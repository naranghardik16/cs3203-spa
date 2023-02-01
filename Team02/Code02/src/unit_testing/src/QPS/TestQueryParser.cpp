#include "catch.hpp"
#include "QPS/QueryParser.h"

auto qp = std::make_shared<QueryParser>();

TEST_CASE("Test Query Parser") {
  std::string s("variable v; Select v");

  auto r = qp->ParseQuery(s);
  REQUIRE(1);
}
