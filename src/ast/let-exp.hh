/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
    /// LetExp.
    class LetExp : public Exp
    {
    public:
        /** \name Ctor & dtor.
         ** \{ */
        /// Construct a LetExp node.
        LetExp(const Location &location, ChunkList *declarations,
               Exp *instructions);
        LetExp(const LetExp &) = delete;
        LetExp &operator=(const LetExp &) = delete;
        /// Destroy a LetExp node.
        ~LetExp() override;
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
        const ChunkList &declarations_get() const;
        /// Return declarations of the statement.
        ChunkList &declarations_get();
        /// Return instructions executed in the statement.
        const Exp &instructions_get() const;
        /// Return instructions executed in the statement.
        Exp &instructions_get();
        /** \} */

    protected:
        /// High bound of the loop.
        ChunkList *declarations_;
        /// Instructions executed in the loop.
        Exp *instructions_;
    };
} // namespace ast
#include <ast/let-exp.hxx>
