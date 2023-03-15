#include "catch.hpp"
#include "QPS/Util/QueryUtil.h"

TEST_CASE("Check if isStmtRef follows rules correctly") {
    SECTION("Test valid cases") {
    std::vector<std::string> valid_vector {"1", "12", "_", "a12AV"};
    for (const auto& kS : valid_vector) {
    REQUIRE(QueryUtil::IsStmtRef(kS));
    }
  }

  SECTION("Test invalid cases") {
  std::vector<std::string> invalid_vector {"0a", "a3432SA!", "01"};
  for (const auto& kS : invalid_vector) {
  REQUIRE_FALSE(QueryUtil::IsStmtRef(kS));
  }
  }
}

TEST_CASE("Check if isEntRef follows rules correctly") {
  SECTION("Test valid cases") {
  std::vector<std::string> valid_vector {"a12AV", "_", "\"a12AV\""};
  for (const auto& kS : valid_vector) {
  REQUIRE(QueryUtil::IsEntRef(kS));
  }
  }

  SECTION("Test invalid cases") {
  std::vector<std::string> invalid_vector {"11", "0", "!", "\"a12AV@\""};
  for (const auto& kS : invalid_vector) {
  REQUIRE_FALSE(QueryUtil::IsEntRef(kS));
  }
  }
}

TEST_CASE("Check if IsDesignEntity follows rules correctly") {
  SECTION("Test valid cases") {
    std::vector<std::string> valid_vector{"stmt", "read", "print", "call", "while", "if",
                                          "assign", "variable", "constant", "procedure"};
    for (const auto& kS : valid_vector) {
      REQUIRE(QueryUtil::IsDesignEntity(kS));
      }
  }

  SECTION("Test invalid cases") {
    std::vector<std::string> valid_vector{"23", ";", "var"};
    for (const auto& kS : valid_vector) {
    REQUIRE_FALSE(QueryUtil::IsDesignEntity(kS));
    }
  }
}
