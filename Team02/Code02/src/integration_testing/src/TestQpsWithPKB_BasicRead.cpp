#include "catch.hpp"

#include <memory>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/PKB.h"
#include "QPS/Qps.h"

TEST_CASE("Check if QPS works with PKB for basic operations") {
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PkbWriteFacade> pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(*pkb);

  pkb_write->AddStatementOfAType("1", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("2", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("3", StatementType::IF);
  pkb_write->AddStatementOfAType("4", StatementType::ASSIGN);
  pkb_write->AddVariable("x");
  pkb_write->AddFollowsRelation("1", "2");
  pkb_write->AddParentRelation("3", "4");
  pkb_write->AddStatementModifyingVariable("1", "x");
  pkb_write->AddStatementModifyingVariable("2", "x");
  pkb_write->AddStatementUsingVariable("2", "x");

  SECTION("Test basic get statements") {
    std::string query = "stmt s; Select s";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1", "2", "3", "4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows") {
    std::string query = "stmt s; Select s such that Follows(s, 2)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows*") {
    std::string query = "stmt s; Select s such that Follows*(s, 2)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent") {
    std::string query = "stmt s; Select s such that Parent(s, 4)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent*") {
    std::string query = "stmt s; Select s such that Parent*(s, 4)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Uses") {
    std::string query = "variable v; Select v such that Uses(2, v)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Modifies") {
    std::string query = "variable v; Select v such that Modifies(1, v)";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"x"};
    REQUIRE(results == expected_results);
  }
}
