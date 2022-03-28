/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>

/// Computing escape and static link related information.
namespace bind
{
    /// Compute the escaping variables.
    misc::error bind_compute(ast::Ast& tree);

} // namespace escapes
