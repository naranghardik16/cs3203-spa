#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename K, typename V>
class OneToManyStore {
 private:
  std::unordered_map<K, std::unordered_set<V>> forward_map_;
  std::unordered_map<V, K> backward_map_;
  std::size_t size = 0;

 public:
  OneToManyStore() = default;
//  ~OneToManyStore();

  void insert(K key, V value);
  bool contains(K key, V value);
  std::size_t length();

  std::unordered_set<V> retrieveFromKey(K key);
  K retrieveFromValue(V value);

  std::vector<std::pair<K, V>> retrieveAll();
  std::unordered_set<K> retrieveAllKeys();
  std::unordered_set<V> retrieveAllValues();
};

#include "OneToManyStore.tpp"
