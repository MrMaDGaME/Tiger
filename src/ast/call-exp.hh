/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
    /// CallExp.
    class CallExp : public Exp
    {
    public:
        /** \name Ctor & dtor.
         ** \{ */
        /// Construct a CallExp node.
        CallExp(const Location &location, misc::symbol name, exps_type *args);
        CallExp(const CallExp &) = delete;
        CallExp &operator=(const CallExp &) = delete;
        /// Destroy a CallExp node.
        ~CallExp() override;
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
        /// Return declarations of the statement.
        const misc::symbol name_get() const;
        /// Return declarations of the statement.
        misc::symbol name_get();
        /// Return instructions executed in the statement.
        const exps_type &args_get() const;
        /// Return instructions executed in the statement.
        exps_type &args_get();
        /// Return definition site.
        const FunctionDec *def_get() const;
        /// Return definition site.
        FunctionDec *def_get();
        /// Set definition site.
        void def_set(FunctionDec *);
        /** \} */

    protected:
        /// High bound of the loop.
        misc::symbol name_;
        /// Instructions executed in the loop.
        exps_type *args_;
        FunctionDec *def_ = nullptr;
    };
} // namespace ast
#include <ast/call-exp.hxx>
