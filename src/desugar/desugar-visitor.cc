/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/algorithm.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace desugar
{
  DesugarVisitor::DesugarVisitor(bool desugar_for_p, bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {}

  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  void DesugarVisitor::operator()(const ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    std::string op = str(e.oper_get());
    const ast::Exp* left = recurse(e.left_get());
    const ast::Exp* right = recurse(e.right_get());

    if (op == "=")
      {
          auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "streq(" << *left << "," << *right << ")"));
          result_ = a;
      }
    else if (op == "<")
      {
          auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "(strcmp(" << *left << "," << *right << ") < 0)"));
          result_ = a;
      }
    else if (op == "<=")
      {
          auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "(strcmp(" << *left << "," << *right << ") <= 0)"));
          result_ = a;
      }
    else if (op == ">=")
      {
          auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "(strcmp(" << *left << "," << *right << ") > 0)"));
          result_ = a;
      }
    else if (op == ">=")
      {
          auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "(strcmp(" << *left << "," << *right << ") >= 0)"));
          result_ = a;
      }
    else
      {
          std::cerr << "\n>>>error<<<\n";
      }
  }

  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  /*<<-
    Desugar `for' loops as `while' loops:

       for i := lo to hi do
         body

     is transformed as:

       let
         var _lo := lo
         var _hi := hi
         var i := _lo
       in
         if i <= _hi then
           while 1 do
             (
               body;
               if i = _hi then
                 break;
               i := i + 1
             )
       end

     Notice that:

     - a `_hi' variable is introduced so that `hi' is evaluated only
       once;

     - a `_lo' variable is introduced to prevent `i' from being in the
       scope of `_hi';

     - a first test is performed before entering the loop, so that the
       loop condition becomes `i < _hi' (instead of `i <= _hi'); this
       is done to prevent overflows on INT_MAX.
       ->>*/

  void DesugarVisitor::operator()(const ast::ForExp& e)
  {
    // FIXME: Some code was deleted here.
    ast::VarDec* vardec = recurse(e.vardec_get());
    ast::Exp* hi = recurse(e.hi_get());
    ast::Exp* body = recurse(e.body_get());

    auto a = std::get<ast::Exp*>(parse::parse(parse::Tweast() << "let\n  var lower := " << *vardec->init_get()
                                                              << "\n  var high := " << *hi
                                                              << "\n  var i := lower"
                                                              << "\nin\n  if i <= high then\n    while 1 do\n      (\n        " << *body
                                                              << ";\n        if i = high then\n          break;\n       i := i + 1\n      )\n end\n"));
    result_ = a;
  }

} // namespace desugar
