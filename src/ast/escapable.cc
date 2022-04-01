/**
 ** \file ast/escapable.cc
 ** \brief Implementation of ast::Escapable.
 */

#include <ast/escapable.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  Escapable::Escapable()
    : is_escaped_(true)
  {}

  bool Escapable::escape_get() const { return is_escaped_; }

  void Escapable::escape_set(bool escape) { is_escaped_ = escape; }
} // namespace ast
