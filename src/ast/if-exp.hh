/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
  public:
      /** \name Ctor & dtor.
       ** \{ */
      /// Construct a IfExp node.
      IfExp(const Location& location, Exp* condition, Exp* body);
      IfExp(const IfExp&) = delete;
      IfExp& operator=(const IfExp&) = delete;
      /// Destroy a IfExp node.
      ~IfExp() override;
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
      /// Return high bound of the loop.
      const Exp& condition_get() const;
      /// Return high bound of the loop.
      Exp& condition_get();
      /// Return instructions executed in the loop.
      const Exp& body_get() const;
      /// Return instructions executed in the loop.
      Exp& body_get();
      /** \} */

  protected:
      /// High bound of the loop.
      Exp* condition_;
      /// Instructions executed in the loop.
      Exp* body_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
