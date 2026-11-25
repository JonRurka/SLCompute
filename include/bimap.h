//
// Created by jon on 11/3/26.
//

#ifndef SLCOMPUTE_BIMAP_H
#define SLCOMPUTE_BIMAP_H

#include <initializer_list>
#include <map>
#include <stdexcept>
#include <utility>

template <typename K, typename V>
class BiMap {
private:
    std::map<K, V> forward;
    std::map<V, K> backward;

public:
    BiMap(std::initializer_list<std::pair<K, V>> entries) {
        for (auto& [k, v] : entries)
            insert(k, v);
    }

    // Inserts a 1-to-1 relationship. Returns false if either key or value exists.
    bool insert(const K& key, const V& value) {
        if (forward.count(key) || backward.count(value)) {
            return false;
        }
        forward[key] = value;
        backward[value] = key;
        return true;
    }

    // Look up Value by Key
    const V& get_value(const K& key) const {
        return forward.at(key); // Throws std::out_of_range if not found
    }

    // Look up Key by Value
    const K& get_key(const V& value) const {
        return backward.at(value); // Throws std::out_of_range if not found
    }

    const bool contains_key(const K& key) const {
        return forward.count(key) > 0;
    }

    const bool contains_value(const V& value) const {
        return backward.count(value) > 0;
    }

    // Erasure handles both sides automatically
    bool erase_by_key(const K& key) {
        auto it = forward.find(key);
        if (it == forward.end()) return false;
        backward.erase(it->second);
        forward.erase(it);
        return true;
    }
};

#endif //SLCOMPUTE_BIMAP_H
