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
        ostr_ << "var " << e.name_get() << " := " << e.var_get() << ";";
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
        ostr_ << "if " << e.condition_get() << "\nthen\n" << misc::incendl
              << e.body_get() << "\n" << misc::decindent;
        if (e.is_else_get())
            ostr_ << "else\n" << misc::incendl << e.body_get() << "\n" << misc::decindent;
    }

    // SeqExp printer
    void PrettyPrinter::operator()(const SeqExp &e)
    {
        for (Exp *exp : e.exps_get())
        {
            ostr_ << *exp;
        }
    }

    // LetExp printer
    void PrettyPrinter::operator()(const LetExp &e)
    {
        ostr_ << "let\n" << misc::incendl << e.declarations_get()
              << misc::decindent << "\nin\n" << misc::incendl << e.instructions_get()
              << "\n" << misc::decindent;
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
        ostr_ << "{";
        std::for_each(e.fields_get().begin(), e.fields_get().end(), [this](auto field){ostr_ << field << ", ";});
        ostr_ << "}";
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
        ostr_ << e.base_type_get();
    }

    void PrettyPrinter::operator()(const CallExp &e) {
        ostr_ << e.name_get() << "(";
        for (size_t i = 0; i < e.args_get().size() - 1; i++) {
            ostr_ << *e.args_get().at(i) << ", ";
        }
        ostr_ << *e.args_get().at(e.args_get().size() - 1);
        ostr_ << ")\n";
    }

    void PrettyPrinter::operator()(const ClassTy &e) {
        ostr_ << "class" << e.super_get() << "{\n" << misc::incendl << e.chunks_get() << "\n" << misc::decendl << "};";
    }

    void PrettyPrinter::operator()(const Field &e) {
        ostr_ << e.name_get() << " : " << e.type_name_get();
    }

    void PrettyPrinter::operator()(const FieldInit &e) {
        ostr_ << "var " << e.name_get() << " := " << e.init_get() << ";";
    }

    void PrettyPrinter::operator()(const IntExp &e) {
        ostr_ << e.value_get();
    }

    void PrettyPrinter::operator()(const MethodCallExp &e) {
        ostr_ << e.object_get() << "." << e.name_get() << "(";
        for (size_t i = 0; i < e.args_get().size() - 1; i++) {
            ostr_ << *e.args_get().at(i) << ", ";
        }
        ostr_ << *e.args_get().at(e.args_get().size() - 1);
        ostr_ << ")\n";
    }

    void PrettyPrinter::operator()(const MethodDec &e) {
        ostr_ << "method " << e.name_get() << "(" << e.formals_get() << ") ";
        if (e.result_get() != nullptr)
            ostr_ << e.result_get() << " ";
        ostr_ << "= (" << e.body_get() << ")\n";
    }

    void PrettyPrinter::operator()(const NameTy &e) {
        ostr_ << e.name_get();
    }

    void PrettyPrinter::operator()(const ObjectExp &e) {
        ostr_ << e.type_name_get();
    }

    void PrettyPrinter::operator()(const RecordTy &e) {
        ostr_ << "(";
        for (size_t i = 0; i < e.fields_get().size() - 1; ++i) {
            ostr_ << *e.fields_get().at(i) << ", ";
        }
        ostr_ << *e.fields_get().at(e.fields_get().size() - 1);
        ostr_ << ")";
    }

    void PrettyPrinter::operator()(const TypeDec &e) {
        ostr_ << e.ty_get() << ";";
    }

    void PrettyPrinter::operator()(const VarDec &e) {
        ostr_ << "var " << e.type_name_get() << " := " << e.init_get() << ";";
    }

    void PrettyPrinter::operator()(const FunctionDec &e) {
        ostr_ << "function " << e.name_get() << "(" << e.formals_get() << ") ";
        if (e.result_get() != nullptr)
            ostr_ << e.result_get() << " ";
        ostr_ << "=\n" << misc::incendl << e.body_get() << "\n" << misc::decendl;
    }

    //
} // namespace ast
