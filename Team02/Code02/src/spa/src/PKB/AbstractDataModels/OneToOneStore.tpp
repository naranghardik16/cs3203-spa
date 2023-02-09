//#include "OneToOneStore.h"

//template<typename K, typename V>
//OneToOneStore<K, V>::~OneToOneStore() {};

template<typename K, typename V>
void OneToOneStore<K, V>::insert(K key, V value) {
  this->forward_map_[key] = value;
  this->backward_map_[value] = key;
  this->size++;
}

template<typename K, typename V>
bool OneToOneStore<K, V>::contains(K key, V value) {
  auto iter = this->forward_map_.find(key);
  return iter != this->forward_map_.end() && iter->second == value;
//  return this->forward_map_.count(key);
}

template<typename K, typename V>
bool OneToOneStore<K, V>::containsKey(K key) {
  return this->forward_map_.find(key) != this->forward_map_.end();
//  return this->forward_map_.count(key);
}

template<typename K, typename V>
bool OneToOneStore<K, V>::containsValue(V value) {
  return this->backward_map_.count(value);
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
