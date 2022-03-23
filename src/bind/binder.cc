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
        e.declarations_get().accept(dynamic_cast<ast::ConstVisitor &>(*this));
        e.instructions_get().accept(dynamic_cast<ast::ConstVisitor &>(*this));
        scope_end();
    }

    void Binder::operator()(ast::SimpleVar& e)
    {

    }

    void Binder::operator()(ast::NameTy& e)
    {

    }

    void Binder::operator()(ast::CallExp& e)
    {

    }

    void Binder::operator()(ast::VarDec& e)
    {
        var_list_.put(e.type_name_get(), e);
    }

    void Binder::operator()(ast::FunctionDec& e)
    {

    }

    void Binder::operator()(ast::TypeDec& e)
    {

    }


    /*-------------------.
    | Visiting VarChunk. |
    `-------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::VarChunk& e)
    {

    }



    /*------------------------.
    | Visiting FunctionChunk. |
    `------------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::FunctionChunk& e)
    {

    }


    /*--------------------.
    | Visiting TypeChunk. |
    `--------------------*/

    // FIXME: Some code was deleted here.

    void Binder::operator()(ast::TypeChunk& e)
    {

    }

} // namespace bind
