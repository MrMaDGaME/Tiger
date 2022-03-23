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
    const misc::error &Binder::error_get() const
    {
        return error_;
    }

    // FIXME: Some code was deleted here (Error reporting).

    void Binder::check_main(const ast::FunctionDec &e)
    {
        // FIXME: Some code was deleted here.
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

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::LetExp &e)
    {
        scope_begin();
        (*this)(e.declarations_get());
        (*this)(e.instructions_get());
        scope_end();
    }

    void Binder::operator()(ast::SimpleVar& e)
    {
        ast::VarDec* var = var_list_.get(e.name_get());
        if (var == nullptr){
            undeclared("SimpleVar", e);
        }
        super_type::operator()(e);
    }

    void Binder::operator()(ast::NameTy& e)
    {
        ast::TypeDec* var = type_list_.get(e.name_get());
        if (var == nullptr){
            undeclared("NameTy", e);
        }
        super_type::operator()(e);
    }

    void Binder::operator()(ast::CallExp& e)
    {
        ast::FunctionDec* var = function_list_.get(e.name_get());
        if (var == nullptr){
            undeclared("CallExp", e);
        }
        super_type::operator()(e);
    }

    void Binder::operator()(ast::VarDec& e)
    {
        ast::VarDec* var = var_list_.get(e.name_get());
        if (var != nullptr){
            redefinition(*var, e);
        }
        var_list_.put(e.name_get(), &e);
        super_type::operator()(e);
    }

    void Binder::operator()(ast::FunctionDec& e)
    {
        ast::FunctionDec* var = function_list_.get(e.name_get());
        if (var != nullptr){
            redefinition(*var, e);
        }
        function_list_.put(e.name_get(), &e);
        scope_begin();
        super_type::operator()(e);
        scope_end();
    }

    void Binder::operator()(ast::TypeDec& e)
    {
        ast::TypeDec* var = type_list_.get(e.name_get());
        if (var != nullptr){
            redefinition(*var, e);
        }
        type_list_.put(e.name_get(), &e);
        super_type::operator()(e);
    }


    /*-------------------.
    | Visiting VarChunk. |
    `-------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::VarChunk& e)
    {
        chunk_visit<ast::VarDec>(e);
    }



    /*------------------------.
    | Visiting FunctionChunk. |
    `------------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::FunctionChunk& e)
    {
        chunk_visit<ast::FunctionDec>(e);
    }


    /*--------------------.
    | Visiting TypeChunk. |
    `--------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::TypeChunk& e)
    {
        chunk_visit<ast::TypeDec>(e);
    }

} // namespace bind
