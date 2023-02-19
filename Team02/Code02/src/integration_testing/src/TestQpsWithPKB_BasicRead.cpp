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

  /*
   *  procedure test {
   * 1  read x;
   * 2  y = x;
   * 3  if (x == 0) then {
   * 4    print x;}
   *    else {
   * 5    while (x > 0) {
   * 6      x = x - 1;}}}
   */
  pkb_write->AddProcedure("test");
  pkb_write->AddStatementOfAType("1", StatementType::READ);
  pkb_write->AddStatementOfAType("2", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("3", StatementType::IF);
  pkb_write->AddStatementOfAType("4", StatementType::PRINT);
  pkb_write->AddStatementOfAType("5", StatementType::WHILE);
  pkb_write->AddStatementOfAType("6", StatementType::ASSIGN);
  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");
  pkb_write->AddFollowsRelation("1", "2");
  pkb_write->AddFollowsRelation("2", "3");
  pkb_write->AddParentRelation("3", "4");
  pkb_write->AddParentRelation("3", "5");
  pkb_write->AddParentRelation("5", "6");
  pkb_write->AddStatementModifyingVariable("1", "x");
  pkb_write->AddStatementModifyingVariable("2", "y");
  pkb_write->AddStatementModifyingVariable("3", "x");
  pkb_write->AddStatementModifyingVariable("5", "x");
  pkb_write->AddStatementModifyingVariable("6", "x");
  pkb_write->AddStatementUsingVariable("2", "x");
  pkb_write->AddStatementUsingVariable("3", "x");
  pkb_write->AddStatementUsingVariable("4", "x");
  pkb_write->AddStatementUsingVariable("5", "x");
  pkb_write->AddStatementUsingVariable("6", "x");

  SECTION("Test basic get procedure") {
    std::string query = "procedure p; Select p";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"test"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get variable") {
    std::string query = "variable v; Select v";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"x", "y"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get procedure") {
    std::string query = "constant c; Select c";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"0", "1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get statements") {
    std::string query = "stmt s; Select s";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get assign statements") {
    std::string query = "assign s; Select s";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"2", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get read statements") {
    std::string query = "read r; Select r";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get print statements") {
    std::string query = "print p; Select p";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get if statements") {
    std::string query = "if ifs; Select ifs";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"3"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get while statements") {
    std::string query = "while w; Select w";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"5"};
    results.sort();
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
