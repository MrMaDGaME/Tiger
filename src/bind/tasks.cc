/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */
#include <ostream>
#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <bind/libbind.hh>
#include <common.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <misc/xalloc.hh>

namespace bind::tasks
{

  /*--------------------.
      | Static Link tasks.  |
      `--------------------*/

  void bind_compute()
  {
    misc::error err = bind::bind_compute(*ast::tasks::the_program);
    task_error() << err;
    if (err)
      task_error().exit();
  }

  void bindings_display() { ast::bindings_display(std::cout) = true; }

  void rename_compute() { bind::rename_compute(*ast::tasks::the_program); }

} // namespace bind::tasks
