/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{
  template <typename Def> misc::symbol Renamer::new_name_compute(const Def& e)
  {
    //FIXME. Map associer le nom a un numero
    misc::symbol name =
      (std::string)e.name_get() + "_" + std::to_string(count_);
    count_++;
    new_names_.insert_or_assign(&e, name);
    return name;
  }

  template <typename Def> misc::symbol Renamer::new_name(const Def& e)
  {
    if (new_names_.contains(&e))
      {
        return new_names_.find(&e)->second;
      }
    return new_name_compute(e);
  }

  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    if (def)
      e.name_set(new_name(*def));
    super_type::operator()(e);
  }

} // namespace bind
