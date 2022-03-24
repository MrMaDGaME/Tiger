/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
    /// ObjectExp.
    class ObjectExp : public Exp
    {
    public:
        /** \name Ctor & dtor.
         ** \{ */
        /// Construct a ObjectExp node.
        ObjectExp(const Location& location, NameTy* type_name);
        ObjectExp(const ObjectExp&) = delete;
        ObjectExp& operator=(const ObjectExp&) = delete;
        /// Destroy a ObjectExp node.
        ~ObjectExp() override;
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
        /** \} */

    protected:
        /// High bound of the loop.
        NameTy* type_name_;
    };
} // namespace ast
#include <ast/object-exp.hxx>
