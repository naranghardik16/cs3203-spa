#include "OneToOneStore.h"

template<typename K, typename V>
OneToOneStore<K, V>::OneToOneStore() {};

template<typename K, typename V>
OneToOneStore<K, V>::~OneToOneStore() {
  delete this->foward_map_;
  delete this->backward_map_;
};

template<typename K, typename V>
void OneToOneStore<K, V>::insert(K key, V value) {
  this->forward_map_[key] = value;
  this->backward_map_[value] = key;
  this->size++;
}

template<typename K, typename V>
bool OneToOneStore<K, V>::contains(K key, V value) {
  return this->forward_map_.contains(key) && this->forward_map_[key] == value;
}

template<typename K, typename V>
std::size_t OneToOneStore<K, V>::length() {
  return this->size;
}

template<typename K, typename V>
V OneToOneStore<K, V>::retrieveFromKey(K key) {
  return this->forward_map_[key];
}

template<typename K, typename V>
K OneToOneStore<K, V>::retrieveFromValue(V value) {
  return this->backward_map_[value];
}

template<typename K, typename V>
std::vector<std::pair<K, V>> OneToOneStore<K, V>::retrieveAll() {
  std::vector<std::pair<K, V>> result;
  for (auto p: this->forward_map_) {
    result.push_back(std::make_pair<K, V>(p.first, p.second));
  }
  return result;
}


template<typename K, typename V>
std::unordered_set<K> OneToOneStore<K, V>::retrieveAllKeys() {
  std::unordered_set<K> result;
  for (auto p: this->forward_map_) {
    result.insert(p.first);
  }
  return result;
}

template<typename K, typename V>
std::unordered_set<V> OneToOneStore<K, V>::retrieveAllValues() {
  std::unordered_set<V> result;
  for (auto p: this->backward_map_) {
    result.insert(p.first);
  }
  return result;
}
