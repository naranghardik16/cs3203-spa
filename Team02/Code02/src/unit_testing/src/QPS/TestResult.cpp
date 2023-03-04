#include "catch.hpp"
#include "QPS/Result.h"
#include <memory>

TEST_CASE("Test Result - Join result") {
  SECTION("Test simple join - preserve row with matching col - success") {
    ResultHeader header_1{{"a", 0}, {"v", 1}};
    ResultTable table_1{{"6", "count"}, {"7", "cenX"}, {"7", "x"}, {"8", "cenY"}, {"8", "y"},
                        {"12", "cenX"}, {"12", "count"}, {"13", "centY"}, {"13", "count"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"a", 0}, {"v", 1}};
    ResultTable table_2{{"6", "count"}, {"7", "cenX"}, {"8", "cenY"}, {"11", "flag"},
                        {"12", "cenX"}, {"13", "centY"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"v", 1}};
    ResultTable expected_table{{"6", "count"}, {"7", "cenX"}, {"8", "cenY"},
                               {"12", "cenX"}, {"13", "centY"}};
    r_1->JoinResult(r_2);
    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test simple join - partially match extends with matching row - success") {
    ResultHeader header_1{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"b", 0}, {"c", 1}, {"e", 2}};
    ResultTable table_2{{"2", "4", "9"},
                        {"2", "2", "8"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}, {"e", 3}};
    ResultTable expected_table{{"1", "2", "4", "9"}, {"1", "2", "2", "8"}};
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test simple join - partially match extends with matching row - success") {
    ResultHeader header_1{{"a", 0}, {"v", 1}};
    ResultTable table_1{{"2", "x"}, {"4", "ost"}, {"6", "ost"}, {"6", "x"}, {"6", "y"}, {"6", "z"},
                        {"6", "wes"}, {"10", "z"}, {"10", "ost"}, {"10", "x"}, {"10", "y"}, {"10", "z"},
                        {"11", "x"}, {"11", "y"}, {"11", "z"}, {"13", "z"}, {"13", "wes"}, {"14", "ost"},
                        {"14", "x"}, {"14", "y"}, {"14", "z"}, {"14", "wes"}, {"17", "z"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"a1", 0}, {"v", 1}};
    ResultTable table_2{{"6", "ost"}, {"10", "wes"}, {"11", "y"}, {"14", "ost"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"v", 1}, {"a1", 2}};
    ResultTable expected_table{{"4", "ost", "6"}, {"4", "ost", "14"}, {"6", "ost", "6"},
                               {"6", "ost", "14"}, {"6", "y", "11"}, {"6", "wes", "10"},
                               {"10", "ost", "6"}, {"10", "ost", "14"}, {"10", "y", "11"},
                               {"11", "y", "11"}, {"13", "wes", "10"}, {"14", "ost", "6"},
                               {"14", "ost", "14"}, {"14", "y", "11"}, {"14", "wes", "10"}};
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test simple join - not match cross product - success") {
    ResultHeader header_1{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"d", 0}, {"e", 1}};
    ResultTable table_2{{"2", "4"},
                        {"2", "2"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4}};
    ResultTable expected_table{{"1", "2", "4", "2", "4"}, {"1", "2", "4", "2", "2"},
                               {"1", "2", "3", "2", "4"}, {"1", "2", "3", "2", "2"},
                               {"1", "2", "2", "2", "4"}, {"1", "2", "2", "2", "2"}};
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test simple join - join with empty table - success") {
    ResultHeader header_1{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"d", 0}};
    ResultTable table_2{};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}};
    ResultTable expected_table{};
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test simple join - empty table join with another table - success") {
    ResultHeader header_1{};
    ResultTable table_1{};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable table_2{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable expected_table{{"1", "2", "4"},
                               {"1", "2", "3"},
                               {"1", "2", "2"}};
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test complex join - multiple join sequence - success") {
    ResultHeader header_1{{"a", 0}, {"b", 1}};
    ResultTable table_1{{"1", "x"},
                        {"2", "y"},
                        {"1", "z"},
                        {"3", "x"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"b", 0}, {"c", 1}};
    ResultTable table_2{{"x", "1"},
                        {"z", "2"},
                        {"y", "7"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader header_3{{"c", 0}, {"a", 1}};
    ResultTable table_3{{"1", "1"},
                        {"2", "2"},
                        {"2", "1"}};
    std::shared_ptr<Result> r_3 = std::make_shared<Result>(header_3, table_3);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable expected_table{{"1", "x", "1"}, {"1", "z", "2"}};
    r_1->JoinResult(r_2);
    r_1->JoinResult(r_3);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }

  SECTION("Test complex join - multiple join sequence different order - success") {
    ResultHeader header_1{{"a", 0}, {"b", 1}};
    ResultTable table_1{{"1", "x"},
                        {"2", "y"},
                        {"1", "z"},
                        {"3", "x"}};
    std::shared_ptr<Result> r_1 = std::make_shared<Result>(header_1, table_1);

    ResultHeader header_2{{"b", 0}, {"c", 1}};
    ResultTable table_2{{"x", "1"},
                        {"z", "2"},
                        {"y", "7"}};
    std::shared_ptr<Result> r_2 = std::make_shared<Result>(header_2, table_2);

    ResultHeader header_3{{"c", 0}, {"a", 1}};
    ResultTable table_3{{"1", "1"},
                        {"2", "2"},
                        {"2", "1"}};
    std::shared_ptr<Result> r_3 = std::make_shared<Result>(header_3, table_3);

    ResultHeader expected_header{{"a", 0}, {"b", 1}, {"c", 2}};
    ResultTable expected_table{{"1", "x", "1"}, {"1", "z", "2"}};
    r_1->JoinResult(r_3);
    r_1->JoinResult(r_2);

    REQUIRE(r_1->header_ == expected_header);
    REQUIRE(r_1->table_ == expected_table);
  }
}
