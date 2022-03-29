/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
    using namespace ast;

    Renamer::Renamer()
        : super_type()
        , new_names_()
    {}


    void Renamer::operator()(ast::VarDec& e)
    {
        visit<ast::VarDec, ast::VarDec>(e, &e);
    }

    void Renamer::operator()(ast::SimpleVar& e)
    {
        visit<ast::SimpleVar, ast::VarDec>(e, e.def_get());
    }

    void Renamer::operator()(ast::FunctionDec& e)
    {
        if (e.body_get() && e.name_get() != "_main")
            visit<ast::FunctionDec, ast::FunctionDec>(e,&e);
        else
        {
            super_type::operator()(e);
        }
    }

    void Renamer::operator()(ast::TypeDec& e)
    {
        visit<ast::TypeDec, ast::TypeDec>(e, &e);
    }

    void Renamer::operator()(ast::CallExp& e)
    {
        if (e.def_get()->body_get())
            visit<ast::CallExp, ast::FunctionDec>(e, e.def_get());
        else
        {
            super_type::operator()(e);
        }
    }

    void Renamer::operator()(ast::NameTy& e)
    {
        visit<ast::NameTy, ast::TypeDec>(e, e.def_get());
    }

} // namespace bind
