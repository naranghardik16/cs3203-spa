template<typename K, typename V>
ManyToManyStore<K, V>::ManyToManyStore() = default;

template<typename K, typename V>
ManyToManyStore<K, V>::~ManyToManyStore() = default;

template<typename K, typename V>
void ManyToManyStore<K, V>::insert(K key, V value) {
  this->forward_map_[key].insert(value);
  this->backward_map_[value].insert(key);

  this->pair_set_.insert(std::make_pair(key, value));
  this->key_set_.insert(key);
  this->value_set_.insert(value);

  this->size++;
}

template<typename K, typename V>
bool ManyToManyStore<K, V>::contains(K key, V value) {
  auto forward_it = this->forward_map_.find(key);
  if (forward_it == this->forward_map_.end()) {
    return false;
  }
  auto backward_it = this->backward_map_.find(value);
  if (backward_it == this->backward_map_.end()) {
    return false;
  }
  return forward_it->second.count(value) > 0 && backward_it->second.count(key) > 0;
}

template<typename K, typename V>
bool ManyToManyStore<K, V>::containsKey(K key) {
  return this->forward_map_.count(key) > 0;
}

template<typename K, typename V>
bool ManyToManyStore<K, V>::containsValue(V value) {
  return this->backward_map_.count(value) > 0;
}

template<typename K, typename V>
std::size_t ManyToManyStore<K, V>::length() {
  return this->size;
}

template<typename K, typename V>
std::size_t ManyToManyStore<K, V>::numberOfKeys() {
  return this->forward_map_.size();
}

template<typename K, typename V>
std::size_t ManyToManyStore<K, V>::numberOfValues() {
  return this->backward_map_.size();
}

template<typename K, typename V>
std::unordered_set<V> ManyToManyStore<K, V>::retrieveFromKey(K key) {
  if (!this->containsKey(key)) return {};
  return this->forward_map_[key];
}

template<typename K, typename V>
std::unordered_set<K> ManyToManyStore<K, V>::retrieveFromValue(V value) {
  if (!this->containsValue(value)) return {};
  return this->backward_map_[value];
}

template<typename K, typename V>
std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> ManyToManyStore<K, V>::retrieveAll() {
  return this->pair_set_;
}

template<typename K, typename V>
std::unordered_set<K> ManyToManyStore<K, V>::retrieveAllKeys() {
  return this->key_set_;
}

template<typename K, typename V>
std::unordered_set<V> ManyToManyStore<K, V>::retrieveAllValues() {
  return this->value_set_;
}

