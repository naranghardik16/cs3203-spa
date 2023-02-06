#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Relational data structure to support One-Many relationships.
 *
 * Supports lookup in forward and backward directions.
 *
 * One-Many relationship is defined as follows:
 * A K key can have multiple V values but
 * Each V value can only have one K key
 *
 * @tparam K - Key of the relation store
 * @tparam V - Value of the relation store
 */
template<typename K, typename V>
class OneToManyStore {
 private:
  std::unordered_map<K, std::unordered_set<V>> forward_map_;
  std::unordered_map<V, K> backward_map_;
  std::size_t size = 0;

 public:
  OneToManyStore() = default;

  /**
   * Insert a K key and a V value into OneToMany store
   *
   * @param key - the key to be inserted
   * @param value - the value to be inserted
   */
  void insert(K key, V value);

  /**
   * Checks if key and value are present in the OneToMany store
   *
   * @param key - the target key to query
   * @param value - the target value to query
   * @return
   */
  bool contains(K key, V value);

  /**
   * Retrieves the number of relations in the store
   *
   * @return The number of relations
   */
  std::size_t length();

  /**
   * Retrieves value from OneToMany store based on key
   *
   * @param key - The key to query
   * @return Set of values
   */
  std::unordered_set<V> retrieveFromKey(K key);

  /**
   * Retrieves key from OneToMany store based on value
   *
   * @param value - The value to query
   * @return the target key
   */
  K retrieveFromValue(V value);

  /**
   * Retrieves all the key-value pairs
   *
   * @return key-value pairs
   */
  std::vector<std::pair<K, V>> retrieveAll();

  /**
   * Retrieves set of keys from OneToMany store
   *
   * @return set of keys
   */
  std::unordered_set<K> retrieveAllKeys();

  /**
   * Retrieves set of all values from OneToMany store
   *
   * @return set of values
   */
  std::unordered_set<V> retrieveAllValues();
};

#include "OneToManyStore.tpp"
