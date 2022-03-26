/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>
#include <misc/contract.hh>

namespace bind
{
    /*-----------------.
    | Error handling.  |
    `-----------------*/

    /// The error handler.
    const misc::error& Binder::error_get() const
    {
        return error_;
    }

    // FIXME: Some code was deleted here (Error reporting).

    void Binder::check_main(const ast::FunctionDec& e)
    {
        if (e.name_get() == "_main")
        {
            std::cout << "Cross\n";
            if (!function_list_.is_unique("_main"))
            {
                error_ << misc::error::error_type::bind << e.location_get() << " : "
                       << "redefinition of _main" << std::endl;
            }
        }
        /*if (e.name_get() != "_main") {
            error_ << misc::error::error_type::bind << e.location_get() << " : "
                   << "cannot find reference to _main" << std::endl;
            error_.exit_on_error();*/
    }

    /*----------------.
    | Symbol tables.  |
    `----------------*/

    void Binder::scope_begin()
    {
        type_list_.scope_begin();
        function_list_.scope_begin();
        var_list_.scope_begin();
    }

    void Binder::scope_end()
    {
        type_list_.scope_end();
        function_list_.scope_end();
        var_list_.scope_end();
    }

    /*---------.
    | Visits.  |
    `---------*/

    void Binder::operator()(ast::LetExp& e)
    {
        scope_begin();
        (*this)(e.declarations_get());
        (*this)(e.instructions_get());
        scope_end();
    }

    void Binder::operator()(ast::WhileExp& e)
    {
        scope_begin();
        loops_.push_back(&e);
        (*this)(e.test_get());
        (*this)(e.body_get());
        loops_.pop_back();
        scope_end();
    }

    void Binder::operator()(ast::ForExp& e)
    {
        scope_begin();
        loops_.push_back(&e);
        var_list_.put(e.vardec_get().name_get(), &e.vardec_get());
        (*this)(e.hi_get());
        (*this)(e.body_get());
        loops_.pop_back();
        scope_end();
    }

    void Binder::operator()(ast::BreakExp& e)
    {
        if (loops_.empty()){
            error(e, "break outside loop");
        }
        e.loop_set(loops_.at(loops_.size() - 1));
    }

    void Binder::operator()(ast::SimpleVar& e)
    {
        ast::VarDec* var = var_list_.get(e.name_get());
        if (var == nullptr)
        {
            undeclared(" " + (std::string)(e.name_get()), e);
        }
        e.def_set(var);
        super_type::operator()(e);
    }

    void Binder::operator()(ast::NameTy& e)
    {
        ast::TypeDec* var = type_list_.get(e.name_get());
        if (var == nullptr && e.name_get() != "int" && e.name_get() != "string")
        {
            undeclared(" " + (std::string)(e.name_get()), e);
        }
        e.def_set(var);
        super_type::operator()(e);
    }


    void Binder::operator()(ast::CallExp& e)
    {
        ast::FunctionDec* var = function_list_.get(e.name_get());
        if (var == nullptr)
        {
            undeclared(" " + (std::string)(e.name_get()), e);
        }
        e.def_set(var);
        super_type::operator()(e);
    }

    /*-------------------.
    | Visiting VarChunk. |
    `-------------------*/

    void Binder::operator()(ast::VarChunk& e)
    {
        chunk_visit<ast::VarDec>(e);
    }

    /*------------------------.
    | Visiting FunctionChunk. |
    `------------------------*/

    void Binder::operator()(ast::FunctionChunk& e)
    {
        chunk_visit<ast::FunctionDec>(e);
    }

    /*--------------------.
    | Visiting TypeChunk. |
    `--------------------*/

    void Binder::operator()(ast::TypeChunk& e)
    {
        chunk_visit<ast::TypeDec>(e);
    }

} // namespace bind
