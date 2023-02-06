//#include "OneToManyStore.h"

template<typename K, typename V>
OneToManyStore<K, V>::OneToManyStore() {};

//template<typename K, typename V>
//OneToManyStore<K, V>::~OneToManyStore() {};

template<typename K, typename V>
void OneToManyStore<K, V>::insert(K key, V value) {
  this->forward_map_[key].insert(value);
  this->backward_map_[value] = key;
  this->size++;
}

template<typename K, typename V>
bool OneToManyStore<K, V>::contains(K key, V value) {
  return this->backward_map_.count(key) && this->backward_map_[key] == value;
}

template<typename K, typename V>
std::size_t OneToManyStore<K, V>::length() {
  return this->size;
}

template<typename K, typename V>
std::vector<V> OneToManyStore<K, V>::retrieveFromKey(K key) {
  return std::vector<K>(this->forward_map_[key].begin(), this->forward_map_[key].end());
}

template<typename K, typename V>
K OneToManyStore<K, V>::retrieveFromValue(V value) {
  return this->backward_map_[value];
}

template<typename K, typename V>
std::vector<std::pair<K, V>> OneToManyStore<K, V>::retrieveAll() {
  std::vector<std::pair<K, V>> result;
  for (auto p: this->backward_map_) {
      result.push_back(std::make_pair<K, V>(p.second, p.first));
  }
  return result;
}

template<typename K, typename V>
std::unordered_set<K> OneToManyStore<K, V>::retrieveAllKeys() {
  std::unordered_set<K> result;
  for (auto p: this->forward_map_) {
    result.insert(p.first);
  }
  return result;
}

template<typename K, typename V>
std::unordered_set<V> OneToManyStore<K, V>::retrieveAllValues() {
  std::unordered_set<V> result;
  for (auto p: this->backward_map_) {
    result.insert(p.first);
  }
  return result;
}


