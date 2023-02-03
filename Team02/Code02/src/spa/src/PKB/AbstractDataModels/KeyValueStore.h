#pragma once

#include <unordered_map>
#include <vector>

template <class Key, class T> class KeyValueStore {
 public:
  using value_type = std::pair<const Key, T>;
  std::unordered_map<Key, T> map;
  std::vector<Key> keys;

  bool insert(const value_type& value) {
    auto [iter, success] = map.insert(value);
    if (success) {
      keys.push_back(value.first);
    }
    return success;
  }

  auto size() const {
    return map.size();
  }
};
