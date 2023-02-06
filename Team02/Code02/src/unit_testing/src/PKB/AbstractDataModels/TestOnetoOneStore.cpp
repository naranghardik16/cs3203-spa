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
//  const std::string tableName = "TestTable";
  OneToOneStore<TestKeys, TestValues> table;
  SECTION("empty state") {
    REQUIRE(table.retrieveFromKey(TEST_KEY2) == DEFAULT_VALUE1);
  }
}