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

  inline const Exp& IfExp::else_clause_get() const { return *else_clause_; }
  inline Exp& IfExp::else_clause_get() { return *else_clause_; }

  inline bool IfExp::is_else_get() const { return is_else_; }
} // namespace ast
