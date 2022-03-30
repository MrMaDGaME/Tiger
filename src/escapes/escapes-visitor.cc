/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{
    // FIXME: Some code was deleted here.
    void EscapesVisitor::operator()(ast::SimpleVar& e)
    {
        auto it = vars_.find(e.def_get());
        if (it != vars_.end() && (*it).second != depth_)
        {
            ast::VarDec *var = (*it).first;
            var->escape_set(true);
            e.def_set(var);
        }
        super_type::operator()(e);
    }

    void EscapesVisitor::operator()(ast::VarDec& e)
    {
        e.escape_set(false);
        vars_.insert_or_assign(&e, depth_);
        super_type::operator()(e);
    }

    void EscapesVisitor::operator()(ast::FunctionDec& e)
    {
        depth_ += 1;
        super_type::operator()(e);
        depth_ -= 1;
    }
} // namespace escapes
