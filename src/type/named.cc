/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  // DONE: Some code was deleted here (Inherited functions).
  void Named::accept(ConstVisitor& v) const{ v(*this); }

  void Named::accept(Visitor& v){ v(*this); }

  // FIXME: Some code was deleted here (Sound).
  bool Named::sound() const
  {
      //cast en Named
      //faire un set, stocker les valeurs 
      //dans une boucle tant que c'est un Named
      // tu continues tout en checkant qu'il existe pas deja dans la liste
      return
      if ()
      a = b;//a c'est ok
      b = a;//b comment ? pas d'argument -_-
  }
  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).

} // namespace type
