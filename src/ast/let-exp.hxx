/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
    inline const Exp& LetExp::declarations_get() const { return *condition_; }
    inline Exp& LetExp::declarations_get() { return *condition_; }

    inline const Exp& LetExp::instructions_get() const { return *body_; }
    inline Exp& LetExp::instructions_get() { return *body_; }
} // namespace ast
