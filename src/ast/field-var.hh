/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    /** \name Ctor & dtor.
         ** \{ */
    /// Construct a FieldVar node.
    FieldVar(const Location& location, Var* var, misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    /// Destroy a FieldVar node.
    ~FieldVar() override;
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
    const misc::symbol name_get() const;
    /// Return instructions executed in the statement.
    misc::symbol name_get();
    /** \} */

  protected:
    /// High bound of the loop.
    Var* var_;
    /// Instructions executed in the loop.
    misc::symbol name_;
  };
} // namespace ast
#include <ast/field-var.hxx>
