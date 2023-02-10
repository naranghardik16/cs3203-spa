
template<typename K, typename V>
ManyToManyStore<K, V>::ManyToManyStore() {};

template<typename K, typename V>
ManyToManyStore<K, V>::~ManyToManyStore() {};

template<typename K, typename V>
void ManyToManyStore<K, V>::insert(K key, V value) {
  this->forward_map_[key].insert(value);
  this->backward_map_[value].insert(key);
}

template<typename K, typename V>
bool ManyToManyStore<K, V>::contains(K key, V value) {
  return this->backward_map_.count(key);
}

template<typename K, typename V>
std::unordered_set<V> ManyToManyStore<K, V>::retrieveFromKey(K key) {
  return this->forward_map_[key];
}

template<typename K, typename V>
std::unordered_set<K> ManyToManyStore<K, V>::retrieveFromValue(V value) {
  return this->backward_map_[value];
}

template<typename K, typename V>
std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> ManyToManyStore<K, V>::retrieveAll() {
  std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> result;
  for (auto p: this->forward_map_) {
    for (auto& s: p.second) {
      result.insert(std::make_pair<K, V>(p.first, s));
    }
  }
  return result;
}

template<typename K, typename V>
std::unordered_set<K> ManyToManyStore<K, V>::retrieveAllKeys() {
  std::unordered_set<K> result;
  for (auto p: this->forward_map_) {
    result.insert(p.first);
  }
  return result;
}

template<typename K, typename V>
std::unordered_set<V> ManyToManyStore<K, V>::retrieveAllValues() {
  std::unordered_set<V> result;
  for (auto p: this->backward_map_) {
    result.insert(p.first);
  }
  return result;
}

