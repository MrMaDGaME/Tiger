/**
 ** \file ast/break-exp.hxx
 ** \brief Inline methods of ast::BreakExp.
 */

#pragma once

#include <ast/break-exp.hh>

// Hint: this needs to be done at TC-3.

namespace ast {
    void BreakExp::loop_set(Exp *loop) {
        loop_ = loop;
    }

    Exp *BreakExp::loop_get() const {
        return loop_;
    }
} // namespace ast
