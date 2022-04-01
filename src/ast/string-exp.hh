/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
         ** \{ */
    /// Construct an StringExp node.
    StringExp(const Location& location, std::string value);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;
    /// Destroy an StringExp node.
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
    /// Return stored string value.
    std::string value_get() const;
    /** \} */

  protected:
    /// Stored string value.
    std::string value_;
  };
} // namespace ast
#include <ast/string-exp.hxx>
