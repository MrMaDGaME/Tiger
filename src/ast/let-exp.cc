/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/let-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
    LetExp::LetExp(const Location& location, Exp* declarations, Exp* instructions)
            : Exp(location)
            , declarations_(declarations)
            , instructions_(instructions)
    {}

    LetExp::~LetExp()
    {
        delete declarations_;
        delete instructions_;
    }

    void LetExp::accept(ConstVisitor& v) const { v(*this); }

    void LetExp::accept(Visitor& v) { v(*this); }
} // namespace ast
