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

#include <type/class.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline std::ostream& operator<<(std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr) && e.escape_get()
          // FIXME: Some code was deleted here.
      )
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.var_get() << '.' << e.name_get();
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

  // If printer
  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "if " << e.condition_get() << " then" << misc::incendl
          << e.body_get() << misc::decendl;
    if (e.is_else_get())
      ostr_ << "else" << misc::incendl << e.else_clause_get()
            << misc::decindent;
  }

  // SeqExp printer
  void PrettyPrinter::operator()(const SeqExp& e)
  {
    if (e.exps_get().size() == 1)
      {
        ostr_ << *e.exps_get()[0];
      }
    else
      {
        ostr_ << '(';
        if (e.exps_get().size() > 0)
          {
            ostr_ << misc::incendl;
            ostr_ << misc::separate(e.exps_get(), std::pair(';', misc::iendl))
                  << misc::decendl;
          }
        ostr_ << ')';
      }
  }

  // LetExp printer
  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incendl << e.declarations_get() << misc::decendl
          << "in" << misc::incendl << e.instructions_get() << misc::decendl
          << "end";
  }

  // OpExp printer
  void PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << e.left_get() << " " << str(e.oper_get()) << " " << e.right_get();
  }

  // BreakExp printer
  void PrettyPrinter::operator()(const BreakExp& e)
  {
    ostr_ << "break"; // e.break_str_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.loop_get() << " */";
  }

  // NilExp printer
  void PrettyPrinter::operator()(const NilExp& e) { ostr_ << "nil"; }

  // ArrayExp printer
  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.type_name_get() << "[" << e.size_get() << "] of "
          << e.init_get();
  }

  // ForExp printer
  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for ";
    if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";

    const Escapable& escaped = e.vardec_get();
    ostr_ << escaped;
    ostr_ << e.vardec_get().name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e.vardec_get() << " */";

    ostr_ << " := " << *(e.vardec_get().init_get()) << " to " << e.hi_get()
          << " do " << misc::incendl << e.body_get() << misc::decindent;
  }

  // While printer
  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";
    if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";

    ostr_ << e.test_get() << misc::iendl << "do " << misc::incendl
          << e.body_get() << misc::decindent;
  }

  // StringExp printer
  void PrettyPrinter::operator()(const StringExp& e) { ostr_ << e.value_get(); }

  // RecordExp printer
  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.type_name_get() << "{";
    for (auto it = e.fields_get().begin(); it != e.fields_get().end(); ++it)
      {
        ostr_ << *(*it);
        if (it != (e.fields_get().end() - 1))
          ostr_ << ", ";
      }

    ostr_ << "}";
  }

  // AssignExp printer
  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get();
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get();
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
    ostr_ << "(";
    if (e.args_get().size() > 0)
      {
        for (size_t i = 0; i < e.args_get().size() - 1; i++)
          {
            ostr_ << *e.args_get().at(i) << ", ";
          }
        ostr_ << *e.args_get().at(e.args_get().size() - 1);
      }
    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << "class";
    ostr_ << " extends " << e.super_get();
    ostr_ << "{" << misc::incendl << e.chunks_get() << misc::decendl << "}";
  }

  void PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }

  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.object_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    ostr_ << "." << e.name_get() << "(";
    if (e.args_get().size() > 0)
      {
        for (size_t i = 0; i < e.args_get().size() - 1; i++)
          {
            ostr_ << *e.args_get().at(i) << ", ";
          }
        ostr_ << *e.args_get().at(e.args_get().size() - 1);
      }
    ostr_ << ")" << misc::iendl;
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << "method " << e.name_get() << "(" << e.formals_get() << ") ";
    if (e.result_get() != nullptr)
      ostr_ << *e.result_get() << " ";
    ostr_ << "= (" << *e.body_get() << ")" << misc::iendl;
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << "new " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << "{";
    if (e.fields_get().size() > 0)
      {
        for (size_t i = 0; i < e.fields_get().size() - 1; ++i)
          {
            ostr_ << *e.fields_get().at(i) << ", ";
          }

        ostr_ << *e.fields_get().at(e.fields_get().size() - 1);
      }
    ostr_ << "}";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";
    ostr_ << " = " << e.ty_get() << misc::iendl /*<< ";"*/;
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    ostr_ << "var ";
    const Escapable& escaped = e;
    ostr_ << escaped;
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    if (e.type_name_get())
      ostr_ << " : " << *e.type_name_get();
    ostr_ << " := " << *(e.init_get()) << misc::iendl;
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    if (e.body_get() == nullptr)
      ostr_ << "primitive ";
    else
      ostr_ << "function ";
    ostr_ << e.name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";
    ostr_ << "(";

    for (auto it = e.formals_get().begin(); it != e.formals_get().end(); ++it)
      {
        Escapable& escaped = **it;
        ostr_ << escaped;
        ostr_ << (*it)->name_get();
        if (bindings_display(ostr_))
          ostr_ << " /* " << *it << " */";

        ostr_ << " : " << *((*it)->type_name_get());
        if (it != (e.formals_get().end() - 1))
          ostr_ << ", ";
      }
    ostr_ << ")";
    if (e.result_get() != nullptr)
      ostr_ << ": " << *e.result_get();
    if (e.body_get())
      {
        ostr_ << " =" << misc::incendl << *e.body_get();
        ostr_ << misc::decindent;
      }
    ostr_ << misc::iendl;
  }

  //
} // namespace ast
