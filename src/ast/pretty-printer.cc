/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e) { ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    ostr_ << "var " << e.name_get() << " := " << e.var_get() ";\n";
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

    // FIXME: Some code was deleted here.
    // If printer
  void PrettyPrinter::operator()(const IfExp& e)
  {
      ostr_ << "if " << e.condition_get() << " then " << misc::incendl <<  e.body_get() << misc::decindent;
      if (e.else_clause_get() != nullptr)
        ostr_ << "else" << misc::incendl << e.body_get() << misc::decindent;
  }

  //SeqExp printer
  void PrettyPrinter::operator()(const SeqExp& e)
  {
      for(Exp* exp : e.exps_get())
      {
          PrettyPrinter::operator()(exp);//Essayer avec * si ca marche pas
      }
  }

  //LetExp printer
  void PrettyPrinter::operator()(const LetExp& e)
  {
      ostr_ << "let" << misc::incendl <<  e.declaration_get() << misc::decindent;
  }

  //OpExp printer
  void PrettyPrinter::operator()(const OpExp& e)
  {
      ostr_ << e.left_get() << " " << e.oper_get() << " " << e.right_get();
  }

  //BreakExp printer
  void PrettyPrinter::operator()(const BreakExp& e)
  {
      ostr_ << e.break_str_get();
  }

  //NilExp printer
  void PrettyPrinter::operator()(const NilExp& e)
  {
      ostr_ << "nil";
  }

  //ArrayExp printer
  void PrettyPrinter::operator()(const ArrayExp& e)
  {
      ostr_ << e.type_name_get() << "[" << e.size_get() << "] of " << e.init_get();
  }

  //ForExp printer
  void PrettyPrinter::operator()(const ForExp& e)
  {
      ostr_ << "for " << PrettyPrinter::operator()(e.vardec_get()) << " to " << e.hi_get() << " do " << PrettyPrinter::operator()(e.body_get());
  }

  //While printer
  void PrettyPrinter::operator()(const WhileExp& e)
  {
      ostr_ << "while " << PrettyPrinter::operator()(e.test_get()) << " do " << PrettyPrinter::operator()(e.body_get());
  }

  //StringExp printer
  void PrettyPrinter::operator()(const StringExp& e)
  {
      ostr_ << e.value_get();
  }

  //RecordExp printer
  void PrettyPrinter::operator()(const RecordExp& e)
  {
      ostr_ << PrettyPrinter::operator()(e.type_name_get()) << ' ' << PrettyPrinter::operator()(e.fields_get());//FIXME: Weird printing
  }

  //ChunkList printer
  void PrettyPrinter::operator()(const ChunkList& e)
  {
      //FIXME: Nani?
  }

  //AssignExp printer
  void PrettyPrinter::operator()(const AssignExp& e)
  {
      ostr_ << PrettyPrinter::operator()(e.var_get()) << " := " << PrettyPrinter::operator()(e.exp_get());
  }

  //
} // namespace ast
