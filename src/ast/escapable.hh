/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>
#include <string>

namespace ast
{
    /// Escapable.
    class Escapable
    {
        // FIXME: Some code was deleted here.
    public:
        Escapable();

        bool escape_get() const;
        void escape_set(bool escape);

    protected:
        bool is_escaped_;
    };
} // namespace ast
#include <ast/escapable.hxx>
