#include "catch.hpp"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include <unordered_set>

enum TestKeys {
  DEFAULT_KEY1,
  TEST_KEY2,
  TEST_KEY3,
  TEST_KEY4,
  TEST_KEY5,
};

enum TestValues {
  DEFAULT_VALUE1,
  TEST_VALUE2,
  TEST_VALUE3,
  TEST_VALUE4,
  TEST_VALUE5,
};

TEST_CASE("AbstractDataModels: OneToMany") {
  OneToManyStore<TestKeys, TestValues> store;
  SECTION("empty store") {
    REQUIRE(store.length() == 0);
    REQUIRE(store.numberOfValues() == 0);
    REQUIRE(store.numberOfKeys() == 0);
    REQUIRE(store.retrieveAllKeys() == std::unordered_set<TestKeys>());
  }

  SECTION("Test to check update and delete operations from OneToMany store") {
    TestKeys test_keys[] = {TEST_KEY2, TEST_KEY3, TEST_KEY4};
    TestValues test_values[] = {TEST_VALUE2, TEST_VALUE3, TEST_VALUE4};
    std::unordered_set<TestKeys> keys;
    std::unordered_set<TestValues> values;
    std::unordered_set<TestValues> valuesSet;
    valuesSet.insert(TEST_VALUE3);
    valuesSet.insert(TEST_VALUE5);
    std::vector<std::pair<TestKeys, TestValues>> entry;
    int i = 0;
    for (TestKeys key: test_keys) {
      TestValues value = test_values[i];
      store.insert(key, value);
      keys.insert(key);
      values.insert(value);
      entry.push_back(std::make_pair(key, value));
      i++;
    }

    REQUIRE(store.retrieveAllKeys() == keys);
    REQUIRE(store.retrieveAllValues() == values);
    REQUIRE(store.containsKey(TEST_KEY2));
    REQUIRE(store.containsValue(TEST_VALUE2));
    REQUIRE_FALSE(store.containsKey(TEST_KEY5));
    REQUIRE_FALSE(store.containsValue(TEST_VALUE5));
    REQUIRE(store.contains(TEST_KEY2, TEST_VALUE2));
    REQUIRE(store.contains(TEST_KEY3, TEST_VALUE3));
    REQUIRE_FALSE(store.contains(TEST_KEY2, TEST_VALUE3));
    REQUIRE_FALSE(store.contains(TEST_KEY3, TEST_VALUE4));
    REQUIRE(store.length() == 3);

    REQUIRE_NOTHROW(store.insert(TEST_KEY3, TEST_VALUE5));
    REQUIRE(store.retrieveFromKey(TEST_KEY3) == valuesSet);
    REQUIRE(store.retrieveFromValue(TEST_VALUE5) == TEST_KEY3);
    REQUIRE(store.length() == 4);
    REQUIRE(store.numberOfKeys() == 3);
    REQUIRE(store.numberOfValues() == 4);
  }
}
