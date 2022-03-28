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
    template<typename Key, typename Data>
    scoped_map<Key, Data>::scoped_map() {
        scope_begin();
    }

    template<typename Key, typename Data>
    scoped_map<Key, Data>::~scoped_map() {
        scope_end();
    }

    template <typename Key, typename Data>
    inline void scoped_map<Key, Data>::put(const Key& key, const Data& value)
    {
        scope_.at(scope_.size() - 1).insert_or_assign(key, value);
    }

    template <typename Key, typename Data>
    inline Data scoped_map<Key, Data>::get(const Key& key) const
    {
        for (auto it = scope_.end() - 1; it != scope_.begin() - 1; it--){
            if ((*it).contains(key))
                return (*it).find(key)->second;
        }
        if (std::is_pointer<Data>::value)
            return nullptr;
        throw std::range_error("cannot find key in scoped_map");
    }

    template <typename Key, typename Data>
    std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
    {
        ostr << "{\n";
        for_each(scope_.begin(), scope_.end(), [this, &ostr](map<Key, Data> map_){
            for_each(map_.begin(), map_.end(), [this, &ostr](Key elt) {
                ostr << elt << " -> " << get(elt) << "\n";
            });
        });
        return ostr << "}";
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_begin()
    {
        scope_.push_back(std::map<Key, Data>());
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_end()
    {
        if (scope_.empty())
            throw std::range_error("trying to end a non-existent scope");
        scope_.pop_back();
    }

    template<typename Key, typename Data>
    bool scoped_map<Key, Data>::is_unique(const Key &key) {
        int count = 0;
        for (auto it = scope_.begin(); it != scope_.end(); ++it){
            if ((*it).contains(key))
                count++;
        }
        return count == 1;
    }

    template <typename Key, typename Data>
    inline std::ostream& operator<<(std::ostream& ostr,
                                    const scoped_map<Key, Data>& tbl)
    {
        return tbl.dump(ostr);
    }

} // namespace misc
