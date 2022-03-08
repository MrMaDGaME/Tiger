/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/if-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
    IfExp::IfExp(const Location& location, Exp* condition, Exp* body, Exp* else_clause)
            : Exp(location)
            , condition_(condition)
            , body_(body)
            , else_clause_(else_clause)
    {}

    IfExp::~IfExp()
    {
        delete condition_;
        delete body_;
        delete else_clause_;
    }

    void IfExp::accept(ConstVisitor& v) const { v(*this); }

    void IfExp::accept(Visitor& v) { v(*this); }
} // namespace ast
