/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
         ** \{ */
    /// Construct a AssignExp node.
    AssignExp(const Location& location, Var* var, Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;
    /// Destroy a AssignExp node.
    ~AssignExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
         ** \{ */
    /// Return declarations of the statement.
    const Var& var_get() const;
    /// Return declarations of the statement.
    Var& var_get();
    /// Return instructions executed in the statement.
    const Exp& exp_get() const;
    /// Return instructions executed in the statement.
    Exp& exp_get();
    /** \} */

  protected:
    /// High bound of the loop.
    Var* var_;
    /// Instructions executed in the loop.
    Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
