/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include <ast/op-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  OpExp::OpExp(const Location& location,
               Exp* left,
               OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void OpExp::accept(ConstVisitor& v) const { v(*this); }

  void OpExp::accept(Visitor& v) { v(*this); }
} // namespace ast

std::string str(ast::OpExp::Oper oper)
{
    switch (oper) {
        case ast::OpExp::Oper::add:
            return std::string("+");
        case ast::OpExp::Oper::sub:
            return std::string("-");
        case ast::OpExp::Oper::mul:
            return std::string("*");
        case ast::OpExp::Oper::div:
            return std::string("/");
        case ast::OpExp::Oper::eq:
            return std::string("=");
        case ast::OpExp::Oper::ne:
            return std::string("<>");
        case ast::OpExp::Oper::lt:
            return std::string("<");
        case ast::OpExp::Oper::le:
            return std::string("<=");
        case ast::OpExp::Oper::gt:
            return std::string(">");
        case ast::OpExp::Oper::ge:
            return std::string(">=");
    }
    throw std::invalid_argument("opExp : str : couldn't find matching operator");
}
