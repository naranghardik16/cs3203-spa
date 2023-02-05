#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename K, typename V>
class OneToOneStore {
 private:
  std::unordered_map<K, V> forward_map_;
  std::unordered_map<K, V> backward_map_;
  std::size_t size = 0;

 public:
  OneToOneStore();
  ~OneToOneStore();

  void insert(K key, V value);
  bool contains(K key, V value);
  std::size_t length();

  V retrieveFromKey(K key);
  K retrieveFromValue(V value);

  std::vector<std::pair<K, V>> retrieveAll();
  std::unordered_set<K> retrieveAllKeys();
  std::unordered_set<V> retrieveAllValues();
};
