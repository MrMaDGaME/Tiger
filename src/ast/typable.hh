/**
 ** \file ast/typable.hh
 ** \brief Declaration of ast::Typable.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::Typable
   ** \brief Hold a type information.
   **
   ** A Typable node holds a type information (type::Type) about
   ** this node.  This can be:
   ** \li the type of the node itself, if it is a Exp or a Ty, or
   ** \li the type of of the declared object, in case of a Dec.
   */

  class Typable
  {
    // FIXME: Some code was deleted here.
  public:
    Typable();

    type::Type* type_get() const
    {
        return type_;
    }

    void type_set(type::Type* type)
    {
        type_ = type;
    }

  protected:
    type::Type* type_;
  };
} // namespace ast
#include <ast/typable.hxx>
