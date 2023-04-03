template<typename K, typename V>
OneToOneStore<K, V>::OneToOneStore() = default;

template<typename K, typename V>
OneToOneStore<K, V>::~OneToOneStore() = default;

template<typename K, typename V>
void OneToOneStore<K, V>::insert(K key, V value) {
  this->forward_map_[key] = value;
  this->backward_map_[value] = key;

  this->pair_set_.insert(std::make_pair(key, value));
  this->key_set_.insert(key);
  this->value_set_.insert(value);

  this->size++;
}

template<typename K, typename V>
bool OneToOneStore<K, V>::contains(K key, V value) {
  auto iter = this->forward_map_.find(key);
  return iter != this->forward_map_.end() && iter->second == value;
}

template<typename K, typename V>
bool OneToOneStore<K, V>::containsKey(K key) {
  return this->forward_map_.count(key) > 0;
}

template<typename K, typename V>
bool OneToOneStore<K, V>::containsValue(V value) {
  return this->backward_map_.count(value) > 0;
}

template<typename K, typename V>
std::size_t OneToOneStore<K, V>::length() {
  return this->size;
}

template<typename K, typename V>
V OneToOneStore<K, V>::retrieveFromKey(K key) {
  if (!containsKey(key)) return V();
  return this->forward_map_[key];
}

template<typename K, typename V>
K OneToOneStore<K, V>::retrieveFromValue(V value) {
  if (!containsValue(value)) return K();
  return this->backward_map_[value];
}

template<typename K, typename V>
std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> OneToOneStore<K, V>::retrieveAll() {
  return this->pair_set_;
}

template<typename K, typename V>
std::unordered_set<K> OneToOneStore<K, V>::retrieveAllKeys() {
  return this->key_set_;
}

template<typename K, typename V>
std::unordered_set<V> OneToOneStore<K, V>::retrieveAllValues() {
  return this->value_set_;
}
