#include "catch.hpp"
#include "QPS/Result.h"

TEST_CASE("Test Result - Join result") {
  SECTION("Test simple join - preserve row with matching col - success") {
    ResultHeader header_1{"a", "v"};
    ResultTable table_1{{"6", "count"}, {"7", "cenX"}, {"7", "x"}, {"8", "cenY"}, {"8", "y"},
                        {"12", "cenX"}, {"12", "count"}, {"13", "centY"}, {"13", "count"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"a", "v"};
    ResultTable table_2{{"6", "count"}, {"7", "cenX"}, {"8", "cenY"}, {"11", "flag"},
                        {"12", "cenX"}, {"13", "centY"}};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{"a", "v"};
    ResultTable expected_table{{"6", "count"}, {"7", "cenX"}, {"8", "cenY"},
                               {"12", "cenX"}, {"13", "centY"}};
    r_1.JoinResult(r_2);
    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test simple join - partially match extends with matching row - success") {
    ResultHeader header_1{"a", "b", "c"};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"b", "c", "e"};
    ResultTable table_2{{"2", "4", "9"},
                        {"2", "2", "8"}};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{"a", "b", "c", "e"};
    ResultTable expected_table{{"1", "2", "4", "9"}, {"1", "2", "2", "8"}};
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test simple join - partially match extends with matching row - success") {
    ResultHeader header_1{"a", "v"};
    ResultTable table_1{{"2", "x"}, {"4", "ost"}, {"6", "ost"}, {"6", "x"}, {"6", "y"}, {"6", "z"},
                        {"6", "wes"}, {"10", "z"}, {"10", "ost"}, {"10", "x"}, {"10", "y"}, {"10", "z"},
                        {"11", "x"}, {"11", "y"}, {"11", "z"}, {"13", "z"}, {"13", "wes"}, {"14", "ost"},
                        {"14", "x"}, {"14", "y"}, {"14", "z"}, {"14", "wes"}, {"17", "z"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"a1", "v"};
    ResultTable table_2{{"6", "ost"}, {"10", "wes"}, {"11", "y"}, {"14", "ost"}};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{"a", "v", "a1"};
    ResultTable expected_table{{"4", "ost", "6"}, {"4", "ost", "14"}, {"6", "ost", "6"},
                               {"6", "ost", "14"}, {"6", "y", "11"}, {"6", "wes", "10"},
                               {"10", "ost", "6"}, {"10", "ost", "14"}, {"10", "y", "11"},
                               {"11", "y", "11"}, {"13", "wes", "10"}, {"14", "ost", "6"},
                               {"14", "ost", "14"}, {"14", "y", "11"}, {"14", "wes", "10"}};
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test simple join - not match cross product - success") {
    ResultHeader header_1{"a", "b", "c"};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"d", "e"};
    ResultTable table_2{{"2", "4"},
                        {"2", "2"}};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{"a", "b", "c", "d", "e"};
    ResultTable expected_table{{"1", "2", "4", "2", "4"}, {"1", "2", "4", "2", "2"},
                               {"1", "2", "3", "2", "4"}, {"1", "2", "3", "2", "2"},
                               {"1", "2", "2", "2", "4"}, {"1", "2", "2", "2", "2"}};
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test simple join - join with empty table - success") {
    ResultHeader header_1{"a", "b", "c"};
    ResultTable table_1{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{};
    ResultTable table_2{};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{"a", "b", "c"};
    ResultTable expected_table{{"1", "2", "4"},
                               {"1", "2", "3"},
                               {"1", "2", "2"}};
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test simple join - empty table join with another table - success") {
    ResultHeader header_1{};
    ResultTable table_1{};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"a", "b", "c"};
    ResultTable table_2{{"1", "2", "4"},
                        {"1", "2", "3"},
                        {"1", "2", "2"}};
    Result r_2(header_2, table_2);

    ResultHeader expected_header{};
    ResultTable expected_table{};
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test complex join - multiple join sequence - success") {
    ResultHeader header_1{"a", "b"};
    ResultTable table_1{{"1", "x"},
                        {"2", "y"},
                        {"1", "z"},
                        {"3", "x"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"b", "c"};
    ResultTable table_2{{"x", "1"},
                        {"z", "2"},
                        {"y", "7"}};
    Result r_2(header_2, table_2);

    ResultHeader header_3{"c", "a"};
    ResultTable table_3{{"1", "1"},
                        {"2", "2"},
                        {"2", "1"}};
    Result r_3(header_3, table_3);

    ResultHeader expected_header{"a", "b", "c"};
    ResultTable expected_table{{"1", "x", "1"}, {"1", "z", "2"}};
    r_1.JoinResult(r_2);
    r_1.JoinResult(r_3);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }

  SECTION("Test complex join - multiple join sequence different order - success") {
    ResultHeader header_1{"a", "b"};
    ResultTable table_1{{"1", "x"},
                        {"2", "y"},
                        {"1", "z"},
                        {"3", "x"}};
    Result r_1(header_1, table_1);

    ResultHeader header_2{"b", "c"};
    ResultTable table_2{{"x", "1"},
                        {"z", "2"},
                        {"y", "7"}};
    Result r_2(header_2, table_2);

    ResultHeader header_3{"c", "a"};
    ResultTable table_3{{"1", "1"},
                        {"2", "2"},
                        {"2", "1"}};
    Result r_3(header_3, table_3);

    ResultHeader expected_header{"a", "b", "c"};
    ResultTable expected_table{{"1", "x", "1"}, {"1", "z", "2"}};
    r_1.JoinResult(r_3);
    r_1.JoinResult(r_2);

    REQUIRE(r_1.header_ == expected_header);
    REQUIRE(r_1.table_ == expected_table);
  }
}
