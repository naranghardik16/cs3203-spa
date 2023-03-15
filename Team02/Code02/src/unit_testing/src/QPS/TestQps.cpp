#include "catch.hpp"
#include "QPS/Qps.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

TEST_CASE("Test Qps") {
  PKB pkb;
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(pkb);
  std::list<std::string> results;

  SECTION("Test valid query - SELECT BOOLEAN") {
    results.clear();
    REQUIRE(results.size() == 0);

    std::string query = "Select BOOLEAN";
    Qps::ProcessQuery(query, results, pkb_read);

    REQUIRE(results.front() == "TRUE");
  }

  SECTION("Test invalid query - wrong select keyword") {
    results.clear();
    REQUIRE(results.size() == 0);

    std::string query = "variable v;select v";
    Qps::ProcessQuery(query, results, pkb_read);

    REQUIRE(results.front() == "SyntaxError");
  }

  SECTION("Test invalid query - wrong relation keyword") {
    results.clear();
    REQUIRE(results.size() == 0);

    std::string query = "variable v;Select v such that Followed(_, _)";
    Qps::ProcessQuery(query, results, pkb_read);

    REQUIRE(results.front() == "SyntaxError");
  }

  SECTION("Test invalid query - undeclared synonym ") {
    results.clear();
    REQUIRE(results.size() == 0);

    std::string query = "variable v;Select v such that Follows(s, _)";
    Qps::ProcessQuery(query, results, pkb_read);

    REQUIRE(results.front() == "SemanticError");
  }

  SECTION("Test invalid query - not ass-syn for pattern clause") {
    results.clear();
    REQUIRE(results.size() == 0);

    std::string query = "variable v;Select v such that Follows(_, _) pattern v(_, _)";
    Qps::ProcessQuery(query, results, pkb_read);

    REQUIRE(results.front() == "SemanticError");
  }
}
