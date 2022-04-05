/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
  /// Array types.
  class Array : public Type
  {
  public:
      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;

      bool compatible_with(const type::Type& other) const override;

      void array_type_set(const type::Type* type);
      const type::Type* array_type_get() const;

  protected:
      mutable const type::Type* array_type_ = nullptr;
  };

} // namespace type

#include <type/array.hxx>
