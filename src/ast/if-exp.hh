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
        IfExp(const Location &location, Exp *condition, Exp *body,
              Exp *else_clause = nullptr);
        IfExp(const IfExp &) = delete;
        IfExp &operator=(const IfExp &) = delete;
        /// Destroy a IfExp node.
        ~IfExp() override;
        /** \} */

        /// \name Visitors entry point.
        /// \{ */
        /// Accept a const visitor \a v.
        void accept(ConstVisitor &v) const override;
        /// Accept a non-const visitor \a v.
        void accept(Visitor &v) override;
        /// \}

        /** \name Accessors.
         ** \{ */
        /// Return condition of the statement.
        const Exp &condition_get() const;
        /// Return condition of the statement.
        Exp &condition_get();
        /// Return body of the statement.
        const Exp &body_get() const;
        /// Return body of the statement.
        Exp &body_get();
        /// Return else_clause of the statement.
        const Exp &else_clause_get() const;
        /// Return else_clause of the statement.
        Exp &else_clause_get();
        /** \} */

    protected:
        /// Condition of the statement.
        Exp *condition_;
        /// Body of the statement.
        Exp *body_;
        /// Else clause of the statement.
        Exp *else_clause_;
    };
} // namespace ast
#include <ast/if-exp.hxx>
