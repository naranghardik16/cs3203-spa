#include "catch.hpp"
#include "QPS/QueryParser.h"

TEST_CASE("Test Query Parser") {
  std::string s("variable v; Select v");

  auto r = QueryParser::ParseQuery(s);
  REQUIRE(1);
}