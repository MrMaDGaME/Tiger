/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

#include <bind/binder.hh>
#include <bind/libbind.hh>

namespace bind
{
    /** Walk the tree, and set the binding flag of variables and arguments
        if they do bind its. */
    misc::error bind_compute(ast::Ast& tree)
    {
        Binder bind_compute;
        bind_compute(tree);
        return bind_compute.error_get();
    }

} // namespace bind
