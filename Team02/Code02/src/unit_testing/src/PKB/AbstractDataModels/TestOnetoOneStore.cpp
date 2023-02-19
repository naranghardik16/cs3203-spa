#include "catch.hpp"
#include "PKB/AbstractDataModels/OneToOneStore.h"

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


TEST_CASE("AbstractDataModels: OneToOne") {
  OneToOneStore<TestKeys, TestValues> store;
  SECTION("Test to check empty OneToOne store") {
    REQUIRE(store.length() == 0);
    REQUIRE(store.retrieveAllKeys() == std::unordered_set<TestKeys>());
    REQUIRE(store.retrieveAllValues() == std::unordered_set<TestValues>());
    REQUIRE(store.retrieveFromKey(TEST_KEY2) == DEFAULT_VALUE1);
    REQUIRE(store.retrieveFromValue(TEST_VALUE2) == DEFAULT_KEY1);
    REQUIRE_FALSE(store.contains(TEST_KEY2, TEST_VALUE2));
  }

  SECTION("Test to check update and delete operations for OneToOne store") {
    std::unordered_set<TestKeys> keys;
    std::unordered_set<TestValues> values;

    std::vector<std::pair<TestKeys, TestValues>> entry;

    TestKeys test_keys[] = {TEST_KEY2, TEST_KEY3};
    TestValues test_values[] = { TEST_VALUE2, TEST_VALUE3};

    int i = 0;
    for (TestKeys key: test_keys) {
      TestValues value = test_values[i];
      store.insert(key, value);
      keys.insert(key);
      values.insert(value);
      entry.push_back(std::make_pair(key, value));
      i++;
    }

    REQUIRE(store.containsKey(TEST_KEY2));
    REQUIRE(store.containsValue(TEST_VALUE2));

    REQUIRE_FALSE(store.containsKey(TEST_KEY4));
    REQUIRE_FALSE(store.containsValue(TEST_VALUE4));

    REQUIRE(store.retrieveAllKeys() == keys);
    REQUIRE(store.retrieveAllValues() == values);

    REQUIRE(store.contains(TEST_KEY2, TEST_VALUE2));
    REQUIRE(store.contains(TEST_KEY3, TEST_VALUE3));

    REQUIRE_FALSE(store.contains(TEST_KEY2, TEST_VALUE3));
    REQUIRE_FALSE(store.contains(TEST_KEY5, TEST_VALUE5));

    REQUIRE(store.retrieveFromValue(TEST_VALUE2) == TEST_KEY2);
    REQUIRE(store.retrieveFromKey(TEST_KEY2) == TEST_VALUE2);

    REQUIRE(store.length() == 2);
  }

  SECTION("Edge cases"){
    REQUIRE_NOTHROW(store.insert(TEST_KEY2, TEST_VALUE2));
  }
}