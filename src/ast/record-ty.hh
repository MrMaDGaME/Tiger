/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{
  /// RecordTy.
  class RecordTy : public Ty
  {
  public:
      /** \name Ctor & dtor.
       ** \{ */
      /// Construct a RecordTy node.
      RecordTy(const Location& location, fieldinits_type* fields);
      RecordTy(const RecordTy&) = delete;
      RecordTy& operator=(const RecordTy&) = delete;
      /// Destroy a RecordTy node.
      ~RecordTy() override;
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
      /// Return instructions executed in the statement.
      const fieldinits_type& fields_get() const;
      /// Return instructions executed in the statement.
      fieldinits_type& fields_get();
      /** \} */

  protected:
      fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-ty.hxx>
