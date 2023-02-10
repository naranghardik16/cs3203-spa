#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "PKB/Util/PairHasherUtil.h"

/**
 * Relational data structure to support One-Many relationships.
 *
 * Supports lookup in forward and backward directions.
 *
 * One-Many relationship is defined as follows:
 * A K key can have multiple V values but each V value
 * can only have one K key.
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
  /**
   * Constructor for OneToManyStore class.
   */
  OneToManyStore();

  /**
   * Destructor for OneToManyStore class.
   */
  ~OneToManyStore();

  /**
   * Inserts a K key and a V value into OneToMany store.
   *
   * @param key - The key to be inserted.
   * @param value - The value to be inserted.
   */
  void insert(K key, V value);

  /**
   * Checks if key and value are present in the OneToMany store.
   *
   * @param key - The target key to query.
   * @param value - The target value to query.
   * @return True if the key-value pair exists in the store, false otherwise.
   */
  bool contains(K key, V value);

  /**
   * Checks if key is present in the OneToMany store.
   *
   * @param key - The target key to query.
   * @return True if the key exists, false otherwise.
   */
  bool containsKey(K key);

  /**
   * Checks if value is present in the OneToMany store.
   *
   * @param value - The target value to query.
   * @return True if the value exists, false otherwise.
   */
  bool containsValue(V value);

  /**
   * Retrieves the number of relations in the store.
   *
   * @return The number of relations present in the store.
   */
  std::size_t length();

  /**
   * Retrieves the number of keys in the OneToMany store.
   *
   * @return The number of keys in the store.
   */
  std::size_t numberOfKeys();

  /**
   * Retrieves the number of values in the OneToMany store.
   *
   * @return The number of values.
   */
  std::size_t numberOfValues();

  /**
   * Retrieves value from OneToMany store based on key.
   *
   * @param key - The key to query for.
   * @return An unordered set of values associated with the key.
   */
  std::unordered_set<V> retrieveFromKey(K key);

  /**
   * Retrieves key from OneToMany store based on a value.
   *
   * @param value - The value to query for.
   * @return The target key.
   */
  K retrieveFromValue(V value);

  /**
   * Retrieves all the key-value pairs.
   *
   * @return An unordered set of key-value pairs.
   */
  std::unordered_set<std::pair<K, V>, PairHasherUtil::hash_pair> retrieveAll();

  /**
   * Retrieves set of keys from OneToMany store.
   *
   * @return An unordered set of all keys present in the store.
   */
  std::unordered_set<K> retrieveAllKeys();

  /**
   * Retrieves set of all values from OneToMany store.
   *
   * @return An unordered set of all values present in the store.
   */
  std::unordered_set<V> retrieveAllValues();
};

#include "OneToManyStore.tpp"
