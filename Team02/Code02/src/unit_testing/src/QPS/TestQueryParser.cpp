#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

TEST_CASE("Test Query Parser") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test valid query") {
    std::string query("variable v; Select a");
    REQUIRE(qp->ParseQuery(query) == "Pass");
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a");
    REQUIRE(qp->ParseQuery(query) == "Syntax Error");
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a such that (1,)");
    REQUIRE(qp->ParseQuery(query) == "Syntax Error");
  }

  SECTION("Test invalid query") {
    std::string query("variable v; Select a such that Follo(1,)");
    REQUIRE(qp->ParseQuery(query) == "Syntax Error");
  }

  SECTION("Test invalid query_v is not stmt ref_throw semantic error") {
    std::string query("variable v; assign a; Select a such that Follows(1,v)");
    REQUIRE(qp->ParseQuery(query) == "Semantic Error");
  }

  SECTION("Test invalid query_synonym not declared_throw semantic error") {
    std::string query("assign a; Select a such that Follows(_,s)");
    REQUIRE(qp->ParseQuery(query) == "Semantic Error");
  }

  SECTION("Test invalid query - invalid wildcard - throw semantic error") {
    std::string query("variable a; Select a such that Uses(_,a)");
    REQUIRE(qp->ParseQuery(query) == "Semantic Error");
  }

  SECTION("Test valid query - valid pattern expr") {
    std::string query("assign a; Select a pattern a(_, _)");
    REQUIRE(qp->ParseQuery(query) == "Pass");
  }

  SECTION("Test invalid query - invalid pattern expr - throw syntax error") {
    std::string query("assign a; Select a such that Follows(a, _) pattern a(_, _\"\")");
    REQUIRE(qp->ParseQuery(query) == "Syntax Error");
  }
}
