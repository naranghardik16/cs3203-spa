#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Relational data structure to support One-One relationships.
 *
 * Supports lookup in forward and backward directions.
 *
 * @tparam K - Key of the relation store
 * @tparam V - Value of the relation store
 */
template<class K, class V>
class OneToOneStore {
 private:
  std::unordered_map<K, V> forward_map_;
  std::unordered_map<V, K> backward_map_;
  std::size_t size = 0;

 public:
  OneToOneStore() = default;
  ~OneToOneStore() = default;

  /**
   * Insert a key and value into OneToOne store
   *
   * @param key - the key to be inserted
   * @param value - the value to be inserted
   */
  void insert(K key, V value);

  /**
   * Checks if key and value are present in the OneToOne store
   *
   * @param key - the target key to query
   * @param value - the target value to query
   * @return true if exists, false otherwise
   */
  bool contains(K key, V value);

  /**
   * Checks if the key is present in the OneToOne store
   *
   * @param key - the target key to query
   * @return true if exists, false otherwise
   */
  bool containsKey(K key);

  /**
   * Checks if the value is present in the OneToOne store
   *
   * @param value - the target value to query
   * @return  true if exists, false otherwise
   */
  bool containsValue(V value);

  /**
   * Retrieves the number of relations in the store
   *
   * @return The number of relations
   */
  std::size_t length();
  /**
   * Retrieves value from OneToOne store based on key
   *
   * @param key - The key to query
   * @return The target value
   */
  V retrieveFromKey(K key);

  /**
   * Retrieves key from OneToOne store based on value
   *
   * @param value - The value to query
   * @return the target key
   */
  K retrieveFromValue(V value);

  /**
   * Retrieve all the key-value pairs
   *
   * @return key-value pairs
   */
  std::vector<std::pair<K, V>> retrieveAll();

  /**
   * Retrieve set of keys from OneToOne store
   *
   * @return set of keys
   */
  std::unordered_set<K> retrieveAllKeys();

  /**
   * Retrieve set of values from OneToOne store
   *
   * @return set of values
   */
  std::unordered_set<V> retrieveAllValues();
};

#include "OneToOneStore.tpp"
