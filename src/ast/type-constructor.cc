/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/type-constructor.hh>
#include <ast/visitor.hh>

namespace ast
{
  TypeConstructor::TypeConstructor(const type::Type* type)
  : type_(type)
  {};

  TypeConstructor::~TypeConstructor()
  {
      delete type_;
  };

  const type::Type* TypeConstructor::type_constructor_get()
  {
      return type_;
  }

  void TypeConstructor::type_constructor_set(const type::Type* type)
  {
      type_ = type;
  }
} // namespace ast
