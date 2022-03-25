/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
    /// BreakExp.
    class BreakExp : public Exp
    {
    public:
        /** \name Ctor & dtor.
         ** \{ */
        /// Construct a BreakExp node.
        BreakExp(const Location& location);
        BreakExp(const BreakExp&) = delete;
        BreakExp& operator=(const BreakExp&) = delete;
        /// Destroy a BreakExp node.
        ~BreakExp() override;
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
        /// Return condition of the statement.
        const Exp& break_str_get() const;
        /// Return condition of the statement.
        Exp& break_str_get();
        /** \} */
        void loop_set(ast::Exp* loop);
        Exp * loop_get() const;

    protected:
        /// String break
        std::string break_str_;
        ast::Exp* loop_;
    };
} // namespace ast
#include <ast/break-exp.hxx>
