#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "PKB/Util/PairHasherUtil.h"

/**
 * Relational data structure to support many-many relationships.
 *
 * Supports lookup in forward and backward directions.
 *
 * ManyToMany relationship is defined as follows:
 * A K key can have multiple V values and a V value can
 * have multiple K keys.
 *
 * @tparam K - Key of the relation store.
 * @tparam V - Value of the relation store.
 */
template<typename K, typename V>
class ManyToManyStore {
 private:
  std::unordered_map<K, std::unordered_set<V>> forward_map_;
  std::unordered_map<V, std::unordered_set<K>> backward_map_;

  std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> pair_set_;
  std::unordered_set<K> key_set_;
  std::unordered_set<V> value_set_;
  std::size_t size;

 public:
  /**
   * Constructor for ManyToManyStore class.
   */
  ManyToManyStore();

  /**
   * Destructor for ManyToManyStore class.
   */
  ~ManyToManyStore();

  /**
   * Insert a K key and a V value into ManyToMany store.
   *
   * @param key - Key to be inserted.
   * @param value - Value to be inserted.
   */
  void insert(K key, V value);

  /**
   * Checks if key and value are present in the ManyToMany store.
   *
   * @param key - The target key to query.
   * @param value - The target value to query.
   * @return True if the key-value pair exists, false otherwise.
   */
  bool contains(K key, V value);

  /**
   * Checks if key is present in the ManyToMany store.
   *
   * @param key - The target key to query.
   * @return True if key exists in the store, false otherwise.
   */
  bool containsKey(K key);

  /**
   * Checks if value is present in the ManyToMany store.
   *
   * @param value - The target value to query.
   * @return True if value exists in the store, false otherwise.
   */
  bool containsValue(V value);

  /**
   * Retrieves the number of relations in the ManyToMany store.
   *
   * @return The number of key-value pairs in the store.
   */
  std::size_t length();

  /**
   * Retrieves the number of keys in the ManyToMany store.
   *
   * @return The number of keys.
   */
  std::size_t numberOfKeys();

  /**
   * Retrieves the number of values in the ManyToMany store.
   *
   * @return The number of values.
   */
  std::size_t numberOfValues();

  /**
   * Retrieves value(s) based on key.
   *
   * @param key - The target key.
   * @return An unordered set of values associated with the key given.
   */
  std::unordered_set<V> retrieveFromKey(K key);

  /**
   * Retrieves key(s) based on value.
   * @param value - The target value.
   * @return An unordered set of keys associated with the value given.
   */
  std::unordered_set<K> retrieveFromValue(V value);

  /**
   * Retrieve all the key-value pairs in the store.
   *
   * @return All the key-value pair in the ManyToMany store.
   */
  std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> retrieveAll();

  /**
   * Retrieve all keys in ManyToMany store.
   *
   * @return An unordered set of keys.
   */
  std::unordered_set<K> retrieveAllKeys();

  /**
   * Retrieve all values in ManyToMany store.
   *
   * @return An unordered set of values.
   */
  std::unordered_set<V> retrieveAllValues();
};

#include "ManyToManyStore.tpp"
