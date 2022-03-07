/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
    inline const Exp& IfExp::condition_get() const { return *condition_; }
    inline Exp& IfExp::condition_get() { return *condition_; }

    inline const Exp& IfExp::body_get() const { return *body_; }
    inline Exp& IfExp::body_get() { return *body_; }
} // namespace ast
