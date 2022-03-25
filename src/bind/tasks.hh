/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#pragma once

#include <task/libtask.hh>

/// The Tasks of the binding module.
namespace bind::tasks
{
    TASK_GROUP("3. Binder");

    /// Compute variables binding.
    TASK_DECLARE("b|bindings-compute",
    "compute the binding variables "
    "and the functions requiring a static link",
    bind_compute, "parse");//changer le bound certainement

    /// Display binded variables.
    TASK_DECLARE("B|bindings-display", "enable binding display in the AST",
    bindings_display, "");

} // namespace escapes::tasks
