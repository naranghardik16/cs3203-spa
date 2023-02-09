#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Relational data structure to support many-many relationships.
 *
 * Supports lookup in forward and backward directions.
 *
 * ManyToMany relationship is defined as follows:
 * A K key can have multiple V values and
 * A V value can have multiple K keys
 *
 * @tparam K - Key of the relation store
 * @tparam V - Value of the relation store
 */
template<typename K, typename V>
class ManyToManyStore {
 private:
  std::unordered_map<K, std::unordered_set<V>> forward_map_;
  std::unordered_map<V, std::unordered_set<K>> backward_map_;

 public:
  /**
   *
   */
  ManyToManyStore();

  /**
   * Insert a K key and a V value into ManyToMany store
   *
   * @param key - the key to be inserted
   * @param value - the value to be inserted
   */
  void insert(K key, V value);

  /**
   * Checks if key and value are present in the ManyToMany store
   *
   * @param key - the target key to query
   * @param value - the target value to query
   * @return true if exists, false otherwise
   */
  bool contains(K key, V value);

  /**
   * Checks if key is present in the ManyToMany store
   *
   * @param key - the target key to query
   * @return true if exists, false otherwise
   */
  bool containsKey(K key);

  /**
   * Checks if value is present in the ManyToMany store
   *
   * @param value - the target value to query
   * @return true if exists, false otherwise
   */
  bool containsValue(V value);

  /**
   * Retrieves the number of relations in the ManyToMany store
   *
   * @return the number of relations
   */
  std::size_t length();

  /**
   * Retrieves the number of keys in the ManyToMany store
   *
   * @return the number of keys
   */
  std::size_t lengthKey();

  /**
   * Retrieves the number of values in the ManyToMany store
   *
   * @return the number of values
   */
  std::size_t lengthValue();


  /**
   * Retrieves value based on key
   *
   * @param key - the target key
   * @return vector of values
   */
  std::vector<V> retrieveFromKey(K key);

  /**
   * Retrieves key based on value
   * @param value - the target value
   * @return vector of keys
   */
  std::vector<K> retrieveFromValue(V value);

  /**
   * Retrieve all the key-value pairs
   *
   * @return key-value pairs
   */
  std::vector<std::pair<K, V>> retrieveAll();

  /**
   * Retrieve all keys in ManyToMany store
   *
   * @return set of keys
   */
  std::unordered_set<K> retrieveAllKeys();

  /**
   * Retrieve all values in ManyToMany store
   *
   * @return set of values
   */
  std::unordered_set<V> retrieveAllValues();
};

#include "ManyToManyStore.tpp"
