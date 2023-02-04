#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

TEST_CASE("Test Query Parser") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test valid query") {
    std::string query("variable v; Select a");
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a such that (1,)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query") {
    std::string query("variable v; Select a such that Follo(1,)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query_v is not stmt ref_throw semantic error") {
    std::string query("variable v; assign a; Select a such that Follows(1,v)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test invalid query_synonym not declared_throw semantic error") {
    std::string query("assign a; Select a such that Follows(_,s)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test invalid query - invalid wildcard - throw semantic error") {
    std::string query("variable a; Select a such that Uses(_,a)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test valid query - valid pattern expr") {
    std::string query("assign a; Select a pattern a(_, _)");
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test invalid query - invalid pattern expr - throw syntax error") {
    std::string query("assign a; Select a such that Follows(a, _) pattern a(_, _\"\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query - invalid pattern expr - throw syntax error") {
    std::string query("stmt a; Select a pattern a(_, _\"x\"_)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }
}
