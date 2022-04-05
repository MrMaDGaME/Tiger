/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
  public:
      TypeConstructor() = default;
      TypeConstructor(const type::Type* type);
      ~TypeConstructor();

      void type_constructor_set(const type::Type* type);
      const type::Type* type_constructor_get();
  protected:
      const type::Type* type_ = nullptr;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
