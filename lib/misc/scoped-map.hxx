/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <range/v3/view/reverse.hpp>
#include <sstream>
#include <stdexcept>
#include <type_traits>

#include "scoped-map.hh"

namespace misc
{
    template <typename Key, typename Data>
    inline void scoped_map<Key, Data>::put(const Key& key, const Data& value)
    {
        if (!map_.contains(key))
            scope_.at(scope_.size() - 1).push_back(key);
        map_.insert_or_assign(key, value);
    }

    template <typename Key, typename Data>
    inline Data scoped_map<Key, Data>::get(const Key& key) const
    {
        if (!map_.contains(key))
        {
            if (std::is_pointer<Data>::value)
                return nullptr;
            throw std::range_error("cannot find key in scoped_map");
        }
        return map_.find(key)->second;
    }

    template <typename Key, typename Data>
    std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
    {
        ostr << "{\n";
        for_each(map_.begin(), map_.end(), [this, &ostr](Key elt) {
            ostr << elt << " -> " << get(elt) << "\n";
        });
        return ostr << "}";
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_begin()
    {
        scope_.push_back(std::vector<Key>());
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_end()
    {
        if (scope_.empty())
            throw std::range_error("trying to end a non-existent scope");
        for (Key k : scope_.at(scope_.size() - 1))
        {
            map_.erase(k);
        }
        scope_.pop_back();
    }

    template <typename Key, typename Data>
    inline std::ostream& operator<<(std::ostream& ostr,
                                    const scoped_map<Key, Data>& tbl)
    {
        return tbl.dump(ostr);
    }

} // namespace misc
