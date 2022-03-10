/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
  public:
      /** \name Ctor & dtor.
       ** \{ */
      /// Construct a RecordExp node.
      RecordExp(const Location& location, NameTy* type_name, fieldinits_type* fields);
      RecordExp(const RecordExp&) = delete;
      RecordExp& operator=(const RecordExp&) = delete;
      /// Destroy a RecordExp node.
      ~RecordExp() override;
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
      const NameTy& type_name_get() const;
      /// Return declarations of the statement.
      NameTy& type_name_get();
      /// Return instructions executed in the statement.
      const fieldinits_type& fields_get() const;
      /// Return instructions executed in the statement.
      fieldinits_type& fields_get();
      /** \} */

  protected:
      NameTy* type_name_;
      fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
