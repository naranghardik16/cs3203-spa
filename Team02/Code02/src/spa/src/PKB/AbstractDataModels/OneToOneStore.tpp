
template<typename K, typename V>
OneToOneStore<K, V>::OneToOneStore() {};

template<typename K, typename V>
OneToOneStore<K, V>::~OneToOneStore() {};

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
  return this->forward_map_.count(key);
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
  if (!containsKey(key)) return "";
  return this->forward_map_[key];
}

template<typename K, typename V>
K OneToOneStore<K, V>::retrieveFromValue(V value) {
  if (!containsValue(value)) return "";
  return this->backward_map_[value];
}

template<typename K, typename V>
std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> OneToOneStore<K, V>::retrieveAll() {
  std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> result;
  for (auto p: this->forward_map_) {
    result.insert(std::make_pair(p.first, p.second));
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
