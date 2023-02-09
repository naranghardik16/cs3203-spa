template<typename K, typename V>
void OneToManyStore<K, V>::insert(K key, V value) {
  this->forward_map_[key].insert(value);
  this->backward_map_[value] = key;
  this->size++;
}

template<typename K, typename V>
bool OneToManyStore<K, V>::contains(K key, V value) {
  auto iter = this->forward_map_.find(key);
  if (iter == this->forward_map_.end()) {
    return false;
  }
  return iter->second.count(value) > 0;
//  return this->backward_map_.count(key) && this->backward_map_[key] == value;
}

template<typename K, typename V>
bool OneToManyStore<K, V>::containsKey(K key) {
  return this->forward_map_.count(key);
}

template<typename K, typename V>
bool OneToManyStore<K, V>::containsValue(V value) {
  return this->backward_map_.count(value);
}

template<typename K, typename V>
std::size_t OneToManyStore<K, V>::length() {
  return this->size;
}

template<typename K, typename V>
std::size_t OneToManyStore<K, V>::lengthKey() {
  return this->forward_map_.size();
}

template<typename K, typename V>
std::size_t OneToManyStore<K, V>::lengthValue() {
  return this->size;
}

template<typename K, typename V>
std::unordered_set<V> OneToManyStore<K, V>::retrieveFromKey(K key) {
  return this->forward_map_[key];
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


