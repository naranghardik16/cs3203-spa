#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename K, typename V>
class ManyToManyStore {
 private:
  std::unordered_map<K, std::unordered_set<V>> forward_map_;
  std::unordered_map<V, std::unordered_set<K>> backward_map_;

 public:
  ManyToManyStore();
//  ~ManyToManyStore();

  void insert(K key, V value);
  bool contains(K key, V value);

  std::unordered_set<V> retrieveFromKey(K key);
  std::vector<K> retrieveFromValue(V value);

  std::vector<std::pair<K, V>> retrieveAll();
  std::unordered_set<K> retrieveAllKeys();
  std::unordered_set<V> retrieveAllValues();
};

#include "ManyToManyStore.tpp"
