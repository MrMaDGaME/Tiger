/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    // DONE: Some code was deleted here.
    if (this != &rhs)
        obj_ = rhs.obj_;
    return *this;
  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    // DONE: Some code was deleted here.
    return obj_ == rhs.obj_;
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    // DONE: Some code was deleted here.
    return obj_ != rhs.obj_;
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    // DONE: Some code was deleted here.
    return ostr << the.get();
  }

} // namespace misc
