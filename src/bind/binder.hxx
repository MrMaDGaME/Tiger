/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
    /*-----------------.
    | Error handling.  |
    `-----------------*/

    void Binder::error(const ast::Ast& loc, const std::string& msg)
    {
        error_ << misc::error::error_type::bind << loc.location_get() << " : "
               << msg << std::endl;
    }

    template <typename T>
    void Binder::undeclared(const std::string& k, const T& e)
    {
        error(e, "undeclared " + k);
    }

    template <typename T>
    void Binder::redefinition(const T& e1, const T& e2)
    {
        error(e1, "redefinition ");
    }

    /*----------------------------.
    | Visiting /ChunkInterface/.  |
    `----------------------------*/

    template <class D>
    void Binder::chunk_visit(ast::Chunk<D>& e)
    {
        // Shorthand.
        using chunk_type = ast::Chunk<D>;
        // on bodies).
        for (auto elt = e.begin(); elt != e.end(); ++elt)
        {
            visit_dec_header(elt);
        }
        for (auto elt = e.begin(); elt != e.end(); ++elt)
        {
            visit_dec_body(elt);
        }
    }

    /* These specializations are in bind/binder.hxx, so that derived
       visitors can use them (otherwise, they wouldn't see them).  */

    template <class D>
    void Binder::visit_dec_header(D& e){
        if (D == ast::Dec)
        (*this)(e);
    }

    template <class D>
    void Binder::visit_dec_body(D& e){
        // FIXME
    }

} // namespace bind
