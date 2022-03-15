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
        /// Output \a e on \a ostr.
        inline std::ostream &operator<<(std::ostream &ostr, const Escapable &e)
        {
            if (escapes_display(ostr)
                // FIXME: Some code was deleted here.
            )
                ostr << "/* escaping */ ";

            return ostr;
        }

        /// \brief Output \a e on \a ostr.
        ///
        /// Used to factor the output of the name declared,
        /// and its possible additional attributes.
        inline std::ostream &operator<<(std::ostream &ostr, const Dec &e)
        {
            ostr << e.name_get();
            if (bindings_display(ostr))
                ostr << " /* " << &e << " */";
            return ostr;
        }
    } // namespace

    PrettyPrinter::PrettyPrinter(std::ostream &ostr)
        : ostr_(ostr)
    {}

    void PrettyPrinter::operator()(const SimpleVar &e)
    {
        ostr_ << e.name_get();
        if (bindings_display(ostr_))
            ostr_ << " /* " << e.def_get() << " */";
    }

    void PrettyPrinter::operator()(const FieldVar &e)
    {
        // FIXME: Some code was deleted here.
        ostr_ << "var " << e.name_get() << " := " << e.var_get() << ";\n";
    }

    /* Foo[10]. */
    void PrettyPrinter::operator()(const SubscriptVar &e)
    {
        ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
              << misc::decindent << ']';
    }

    void PrettyPrinter::operator()(const CastExp &e)
    {
        ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
    }

    // If printer
    void PrettyPrinter::operator()(const IfExp &e)
    {
        ostr_ << "if " << e.condition_get() << " then " << misc::incendl
              << e.body_get() << misc::decindent;
        // if (e.else_clause_get() == 0) //bizar bizar ca marchait avant FIXME ?
        ostr_ << "else" << misc::incendl << e.body_get() << misc::decindent;
    }

    // SeqExp printer
    void PrettyPrinter::operator()(const SeqExp &e)
    {
        for (Exp *exp : e.exps_get())
        {
            PrettyPrinter::operator()(exp); // Essayer avec * si ca marche pas
        }
    }

    // LetExp printer
    void PrettyPrinter::operator()(const LetExp &e)
    {
        ostr_ << "let" << misc::incendl << e.declarations_get()
              << misc::decindent;
    }

    // OpExp printer
    void PrettyPrinter::operator()(const OpExp &e)
    {
        ostr_ << e.left_get() << " " << str(e.oper_get()) << " "
              << e.right_get();
    }

    // BreakExp printer
    void PrettyPrinter::operator()(const BreakExp &e)
    {
        ostr_ << "break"; // e.break_str_get();
    }

    // NilExp printer
    void PrettyPrinter::operator()(const NilExp &e)
    {
        (void)e;
        ostr_ << "nil";
    }

    // ArrayExp printer
    void PrettyPrinter::operator()(const ArrayExp &e)
    {
        ostr_ << e.type_name_get() << "[" << e.size_get() << "] of "
              << e.init_get();
    }

    // ForExp printer
    void PrettyPrinter::operator()(const ForExp &e)
    {
        ostr_ << "for " << e.vardec_get() << " to " << e.hi_get() << " do "
              << e.body_get();
    }

    // While printer
    void PrettyPrinter::operator()(const WhileExp &e)
    {
        ostr_ << "while " << e.test_get() << " do " << e.body_get();
    }

    // StringExp printer
    void PrettyPrinter::operator()(const StringExp &e)
    {
        ostr_ << e.value_get();
    }

    // RecordExp printer
    void PrettyPrinter::operator()(const RecordExp &e)
    {
        ostr_ << "type " << e.type_name_get() << " = {";
        std::for_each(e.fields_get().begin(), e.fields_get().end(), [this](auto field){ostr_ << field->name_get() << " : " << field->init_get() << ", ";});
        ostr_ << "}\n";
        // Weird printing //fields_init is an array of field-init
    }

    // ChunkList printer
    void PrettyPrinter::operator()(const ChunkList &e)
    {
        // FIXME: Nani?
    }

    // AssignExp printer
    void PrettyPrinter::operator()(const AssignExp &e)
    {
        ostr_ << e.var_get() << " := " << e.exp_get();
    }

    void PrettyPrinter::operator()(const ArrayTy &e)
    {
        // FIXME
    }

    void PrettyPrinter::operator()(const CallExp &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const ClassTy &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const Field &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const FieldInit &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const IntExp &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const MethodCallExp &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const MethodDec &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const NameTy &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const ObjectExp &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const RecordTy &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const TypeDec &e) {
        // FIXME
    }

    void PrettyPrinter::operator()(const VarDec &e) {
        // FIXME
    }

    //
} // namespace ast
