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

    inline void Binder::error(const ast::Ast& loc, const std::string& msg)
    {
        error_ << misc::error::error_type::bind << loc.location_get() << " : "
               << msg << std::endl;
        error_.exit_on_error();
    }

    template <typename T>
    void Binder::undeclared(const std::string& k, const T& e)
    {
        error(e, "undeclared type:" + k);
    }

    template <typename T>
    void Binder::redefinition(const T& e1, const T& e2)
    {
        error(e1, "redefinition: " + (std::string)(e1.name_get()));
    }

    /*----------------------------.
    | Visiting /ChunkInterface/.  |
    `----------------------------*/

    template <class D>
    void Binder::chunk_visit(ast::Chunk<D>& e)
    {
        std::set<misc::symbol> fun_list;
        // Shorthand.
        using chunk_type = ast::Chunk<D>;
        // on bodies).
        for (auto elt : e)
        {
            if (fun_list.contains(elt->name_get()))
            {
                redefinition(*elt, *elt);
            }
            fun_list.insert(elt->name_get());
            visit_dec_header(*elt);
        }
        for (auto elt : e)
        {
            visit_dec_body(*elt);
        }
    }

    /* These specializations are in bind/binder.hxx, so that derived
       visitors can use them (otherwise, they wouldn't see them).  */

    template <>
    inline void Binder::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e){
        check_main(e);
        function_list_.put(e.name_get(), &e);
    }

    template <>
    inline void Binder::visit_dec_header<ast::VarDec>(ast::VarDec& e){
        var_list_.put(e.name_get(), &e);
    }

    template <>
    inline void Binder::visit_dec_header<ast::TypeDec>(ast::TypeDec& e){
        type_list_.put(e.name_get(), &e);
        super_type::operator()(e);
    }

    template <>
    inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e){
        scope_begin();
        super_type::operator()(e);
        scope_end();
    }

    template <>
    inline void Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e){
        super_type::operator()(e);
    }

    template <>
    inline void Binder::visit_dec_body<ast::TypeDec>(ast::TypeDec& e){
        super_type::operator()(e);
    }

} // namespace bind
