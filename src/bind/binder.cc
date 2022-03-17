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
        e.declarations_get().accept(*this);
        e.instructions_get().accept(*this);
        scope_end();
    }

    /*-------------------.
    | Visiting VarChunk. |
    `-------------------*/

    // FIXME: Some code was deleted here.

    /*------------------------.
    | Visiting FunctionChunk. |
    `------------------------*/

    // FIXME: Some code was deleted here.

    /*--------------------.
    | Visiting TypeChunk. |
    `--------------------*/
    // FIXME: Some code was deleted here.

} // namespace bind
