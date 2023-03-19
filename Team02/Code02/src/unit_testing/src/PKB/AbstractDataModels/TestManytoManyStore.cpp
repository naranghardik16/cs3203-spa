#include "catch.hpp"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

enum TestKeys {
  TEST_KEY1,
  TEST_KEY2,
  TEST_KEY3,
  TEST_KEY4,
};

enum TestValues {
  TEST_VALUE1,
  TEST_VALUE2,
  TEST_VALUE3,
  TEST_VALUE4,
};

TEST_CASE("AbstractDataModels: ManyToMany") {
  ManyToManyStore<TestKeys, TestValues> store;
  SECTION("Test to check empty ManyToMany store") {
    REQUIRE(store.length() == 0);
    REQUIRE(store.numberOfValues() == 0);
    REQUIRE(store.numberOfKeys() == 0);
    REQUIRE_FALSE(store.containsValue(TEST_VALUE1));
    REQUIRE_FALSE(store.containsKey(TEST_KEY1));
    REQUIRE_FALSE(store.contains(TEST_KEY1, TEST_VALUE1));
    REQUIRE(store.retrieveAllValues() == std::unordered_set<TestValues>({}));
  }

  SECTION("Test to check update and delete operations for ManyToMany store") {
    TestKeys test_keys[] = {TEST_KEY1, TEST_KEY2, TEST_KEY3};
    TestValues test_values[] = {TEST_VALUE1, TEST_VALUE2, TEST_VALUE3};
    std::unordered_set<TestKeys> keys;
    std::unordered_set<TestValues> values;
    std::vector<TestValues> valueSet1;
    std::vector<TestValues> valueSet2;
    std::vector<TestKeys> keysSet1;
    std::vector<TestKeys> keysSet2;
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

    REQUIRE(store.numberOfKeys() == 3);
    REQUIRE(store.length() == 3);
    REQUIRE(store.numberOfValues() == 3);
    REQUIRE(store.retrieveAllKeys() == keys);
    REQUIRE(store.retrieveAllValues() == values);
    REQUIRE_NOTHROW(store.insert(TEST_KEY1, TEST_VALUE1));

    REQUIRE(store.containsKey(TEST_KEY1));
    REQUIRE(store.containsValue(TEST_VALUE1));
    REQUIRE_FALSE(store.containsValue(TEST_VALUE4));
    REQUIRE_FALSE(store.containsKey(TEST_KEY4));

    valueSet1.push_back(TEST_VALUE2);
    valueSet1.push_back(TEST_VALUE4);
    keysSet1.push_back(TEST_KEY2);

    REQUIRE_NOTHROW(store.insert(TEST_KEY2, TEST_VALUE4));
  }
}
