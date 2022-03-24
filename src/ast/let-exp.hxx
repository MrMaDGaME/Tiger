/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
    inline const ChunkList& LetExp::declarations_get() const
    {
        return *declarations_;
    }
    inline ChunkList& LetExp::declarations_get()
    {
        return *declarations_;
    }

    inline const Exp& LetExp::instructions_get() const
    {
        return *instructions_;
    }
    inline Exp& LetExp::instructions_get()
    {
        return *instructions_;
    }
} // namespace ast
