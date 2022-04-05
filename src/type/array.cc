/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <type/array.hh>
#include <type/visitor.hh>

namespace type
{
    void Array::accept(ConstVisitor& v) const { v(*this); }

    void Array::accept(Visitor& v){ v(*this); }

    bool compatible_with(const type::Type& other)
    {
        return true;
    }
    void Array::array_type_set(const type::Type* type)
    {
        array_type_ = type;
    }

    const type::Type* Array::array_type_get() const
    {
        return array_type_;
    }
} // namespace type
