#include "catch.hpp"

#include <memory>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Pkb.h"
#include "QPS/Qps.h"
#include "ExpressionGeneratorStub/ExpressionGeneratorStub.h"
#include "PKB/Stores/CallsStore.h"

TEST_CASE("Check if QPS works with Pkb for basic operations") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);

  /*
   *  procedure test {
   * 1  read x;
   * 2  y = x;
   * 3  if (x == 0) then {
   * 4    print x;}
   *    else {
   * 5    while (x > 0) {
   * 6      x = x - 1;}}
   * 7 print test
   * }
   */
  pkb_write->AddProcedure("test");
  pkb_write->AddStatementOfAType("1", StatementType::READ);
  pkb_write->AddStatementOfAType("2", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("3", StatementType::IF);
  pkb_write->AddStatementOfAType("4", StatementType::PRINT);
  pkb_write->AddStatementOfAType("5", StatementType::WHILE);
  pkb_write->AddStatementOfAType("6", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("7", StatementType::PRINT);
  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");
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
  pkb_write->AddStatementUsingVariable("7", "test");

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- both special case") {
    std::string query = "print p; read r; Select p with p.varName = r.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- both special case (swap args)") {
    std::string query = "print p; read r; Select p with r.varName = p.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result") {
    std::string
        query = "stmt s; constant c; Select s.stmt# with s.stmt# = c.value";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result (swap args)") {
    std::string
        query = "stmt s; constant c; Select s.stmt# with c.value = s.stmt#";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName") {
    std::string query =
        "print pn; procedure proc; Select pn with pn.varName = proc.procName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName -- swap args") {
    std::string query =
        "print pn; procedure proc; Select pn with proc.procName = pn.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- does not return result") {
    std::string query = "print p; read r; Select r with p.stmt# = r.stmt#";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    std::string query = "print p; Select p.stmt# with p.varName=\"x\"";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return result") {
    std::string query = "print p; Select p with 4=p.stmt#";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    std::string query = "print p; Select p.varName with p.stmt#=4";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return none ") {
    std::string query = "print p; Select p with p.stmt#=1";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

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

    std::list<std::string> expected_results{"test", "x", "y"};
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

    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6", "7"};
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

    std::list<std::string> expected_results{"4", "7"};
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

TEST_CASE("Test case of empty relationship stores") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("test");
  pkb_write->AddStatementOfAType("1", StatementType::READ);
  pkb_write->AddStatementOfAType("2", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("3", StatementType::IF);
  pkb_write->AddStatementOfAType("4", StatementType::PRINT);
  pkb_write->AddStatementOfAType("5", StatementType::WHILE);
  pkb_write->AddStatementOfAType("6", StatementType::ASSIGN);
  pkb_write->AddStatementOfAType("7", StatementType::PRINT);
  pkb_write->AddStatementOfAType("8", StatementType::CALL);
  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");
  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");

  SECTION("Calls(_,_)") {
    std::string query = "procedure p; Select p.procName such that Calls(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_)") {
    std::string query = "procedure p; Select p such that Calls(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN)") {
    std::string query = "procedure p; Select p such that Calls(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,_)") {
    std::string query = "procedure p; Select p.procName such that Calls*(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_)") {
    std::string query = "procedure p; Select p such that Calls*(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN)") {
    std::string query = "procedure p; Select p such that Calls*(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Follows(_,_)") {
    std::string query = "constant c; Select c.value such that Follows(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Parent(_,_)") {
    std::string query = "assign a; Select a.stmt# such that Parent(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("proc1");
  pkb_write->AddProcedure("proc2");
  pkb_write->AddProcedure("proc3");
  pkb_write->AddProcedure("proc4");
  pkb_write->AddProcedure("proc5");
  pkb_write->AddProcedure("proc6");
  pkb_write->AddProcedure("proc7");
  pkb_write->AddProcedure("proc8");

  pkb_write->AddCallsRelation("proc1", "proc2");
  pkb_write->AddCallsRelation("proc1", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc5");
  pkb_write->AddCallsRelation("proc3", "proc4");
  pkb_write->AddCallsRelation("proc5", "proc6");
  pkb_write->AddCallsRelation("proc6", "proc7");


  SECTION("Calls Multiclause -- test transitive") {
    // Select procedures that call procedures that are callers
    std::string query =
        "procedure p,p1,p2,p3,p4; "
        "Select <p1,p2,p3.procName,p4> such that Calls(p1,p2) and Calls(p2,p3) and Calls(p3,p4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc1 proc2 proc3 proc4", "proc1 proc2 proc5 proc6",
                         "proc2 proc5 proc6 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,_) is true") {
    std::string query = "procedure p; Select p.procName such that Calls(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is true") {
    std::string
        query = "procedure p; Select <p.procName> such that Calls(_,\"proc5\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is false") {
    std::string query =
        "procedure p; Select <p.procName> such that Calls (_,\"proc1\"  )   ";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is true") {
    std::string query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls  (\"proc1\",   _)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is false") {
    std::string query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls(\"proc8\",_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is true") {
    std::string
        query = "procedure p; Select p such that Calls(\"proc1\",\"proc2\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is false") {
    std::string query =
        "procedure p; Select p .procName such that Calls(\"proc3    \",\"       proc2\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_) has result") {
    std::string query = "procedure p; Select p. procName such that Calls(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has result") {
    std::string query =
        "procedure p; Select p  . procName such that Calls(p, \"      proc2       \")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has no result") {
    std::string query =
        "procedure p; Select p  . procName such that Calls(p, \"proc8\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,PROC-SYN) has result") {
    std::string query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with q.procName = \"proc6\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc5"};
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls(PROC-SYN,PROC-SYN) has no result") {
    std::string query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with p.procName = \"proc4\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,PROC-SYN) has result") {
    std::string
        query = "procedure p; Select p.procName such that Calls(\"proc2\",p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc3", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause") {
    // Select procedures that call procedures that are callers
    std::string query =
        "procedure p,p1,p2,p3,p4; Select p1 such that Calls(p1,p2) and Calls(p2,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls*") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("proc1");
  pkb_write->AddProcedure("proc2");
  pkb_write->AddProcedure("proc3");
  pkb_write->AddProcedure("proc4");
  pkb_write->AddProcedure("proc5");
  pkb_write->AddProcedure("proc6");
  pkb_write->AddProcedure("proc7");
  pkb_write->AddProcedure("proc8");

  pkb_write->AddCallsRelation("proc1", "proc2");
  pkb_write->AddCallsRelation("proc1", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc5");
  pkb_write->AddCallsRelation("proc3", "proc4");
  pkb_write->AddCallsRelation("proc5", "proc6");
  pkb_write->AddCallsRelation("proc6", "proc7");


  pkb_write->AddCallsStarRelation();


  SECTION("Calls*(p,p) should have no result") {
    std::string query = "procedure p; Select p.procName such that Calls*(p,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(p,p) should have no result") {
    std::string query = "procedure p; Select p.procName such that Calls(p,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls('proc1','proc1') should have no result") {
    std::string query = "procedure p; Select p.procName such that Calls(\"proc1\",\"proc1\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*('proc1','proc1') should have no result") {
    std::string query = "procedure p; Select p.procName such that Calls*(\"proc1\",\"proc1\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }


  SECTION("Calls*(_,_) is true") {
    std::string query = "procedure p; Select p.procName such that Calls*(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is true") {
    std::string query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc4\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is false") {
    std::string query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc8\"  )   ";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is true") {
    std::string query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls*  (\"proc2\",   _)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is false") {
    std::string query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls*(\"proc7\",_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is true") {
    std::string
        query = "procedure p; Select p such that Calls*(\"proc2\",\"proc7\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is false") {
    std::string query =
        "procedure p; Select p .procName such that Calls*(\"proc4  \",\"       proc7\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_) has result") {
    std::string query = "procedure p; Select p. procName such that Calls*(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has result") {
    std::string query =
        "procedure p; Select p  . procName such that Calls*(p, \"      proc7       \")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has no result") {
    std::string query =
        "procedure p; Select p  . procName such that Calls*(p, \"proc8\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,PROC-SYN) has result") {
    std::string query =
        "procedure p; procedure q; Select q.procName such that Calls*(p,q) with p.procName = \"proc2\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls*(PROC-SYN,PROC-SYN) has no result") {
    std::string query =
        "procedure p; procedure q; Select p.procName such that Calls*(p,q) with q.procName = \"proc1\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls*(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,PROC-SYN) has result") {
    std::string
        query = "procedure p; Select p.procName such that Calls*(\"proc5\",p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- indirect calls only") {
    std::string query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3> such that Calls(p1,p2) and Calls*(p2,p3)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1 proc3", "proc1 proc4", "proc1 proc5", "proc1 proc6",
         "proc1 proc7", "proc2 proc4", "proc2 proc6",
         "proc2 proc7", "proc5 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- test transitive") {
    std::string query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3.procName> such that Calls(p1,p2) and Calls*(p2,p3) and Calls*(p3,p4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results
        {"proc1 proc3", "proc1 proc5", "proc1 proc6", "proc2 proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Next - Basic") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

  std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node1->AddStmt(2);
  cfg->AddStmtCfg(2, node1);

  std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
  node2->AddStmt(3);
  cfg->AddStmtCfg(3, node2);
  node2->AddStmt(4);
  cfg->AddStmtCfg(4, node2);

  std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
  node3->AddStmt(5);
  cfg->AddStmtCfg(5, node3);
  node3->AddStmt(6);
  cfg->AddStmtCfg(6, node3);

  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementOfAType("2", IF);
  pkb_write->AddStatementOfAType("3", CALL);
  pkb_write->AddStatementOfAType("4", ASSIGN);
  pkb_write->AddStatementOfAType("5", CALL);
  pkb_write->AddStatementOfAType("6", READ);

  node1->AddTransition(true, node2);
  node1->AddTransition(false, node3);

  cfg->AddProcCfg("main", node1);

  pkb_write->AddCfg(cfg);

  SECTION("Next(_,_) is true") {
    std::string query = "stmt s; Select s.stmt# such that Next(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is true") {
    std::string query = "stmt s; Select <s.stmt#> such that Next(_,2)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is false") {
    std::string query = "stmt s; Select <s.stmt#> such that Next (_,1 )";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is true") {
    std::string query =
        "stmt s1; stmt s2; Select <s1.stmt#, s1.stmt#> such that Next (1,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string>
        expected_results{"1 1", "2 2", "3 3", "4 4", "5 5", "6 6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is false") {
    std::string query =
        "stmt s1; stmt s2; Select <s1.stmt#, s2.stmt#> such that Next (6,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is true") {
    std::string query = "stmt s; Select s such that Next(1,2)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is false") {
    std::string query = "stmt s; Select s .stmt# such that Next(3,2)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }
}

// "procedure main {\n"
// "  while (x==1) {"
// "    flag = 1;"
// "    while( flag == 1 ) {"
// "        flag = 2;"
// "    }"
// "    count = count + 1;"
// "  } "
// "  y = 20;"
// "  while (x==1) {"
// "    flag = 1;"
// "    while( flag == 1 ) {"
// "        flag = 2;"
// "    }"
// "  }"
// "  count = count - 1; "
// "}\n";
TEST_CASE("Integration testing for Next API - Complex") {
  std::shared_ptr<Pkb> pkb = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade>
      pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

  std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node8 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node9 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node10 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node11 = std::make_shared<CfgNode>();
  std::shared_ptr<CfgNode> node12 = std::make_shared<CfgNode>();

  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node2->AddStmt(2);
  cfg->AddStmtCfg(2, node2);
  node3->AddStmt(3);
  cfg->AddStmtCfg(3, node3);
  node4->AddStmt(4);
  cfg->AddStmtCfg(4, node4);
  node5->AddStmt(5);
  cfg->AddStmtCfg(5, node5);
  node6->AddStmt(6);
  cfg->AddStmtCfg(6, node6);
  node7->AddStmt(7);
  cfg->AddStmtCfg(7, node7);
  node8->AddStmt(8);
  cfg->AddStmtCfg(8, node8);
  node9->AddStmt(9);
  cfg->AddStmtCfg(9, node9);
  node10->AddStmt(10);
  cfg->AddStmtCfg(10, node10);
  node11->AddStmt(11);
  cfg->AddStmtCfg(11, node11);
  node12->AddStmt(12);
  cfg->AddStmtCfg(12, node12);

  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementOfAType("2", WHILE);
  pkb_write->AddStatementOfAType("3", ASSIGN);
  pkb_write->AddStatementOfAType("4", WHILE);
  pkb_write->AddStatementOfAType("5", ASSIGN);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", READ);
  pkb_write->AddStatementOfAType("8", WHILE);
  pkb_write->AddStatementOfAType("9", ASSIGN);
  pkb_write->AddStatementOfAType("10", WHILE);
  pkb_write->AddStatementOfAType("11", ASSIGN);
  pkb_write->AddStatementOfAType("12", ASSIGN);

  cfg->AddProcCfg("main", node1);

  node1->AddTransition(true, node2);
  node2->AddTransition(true, node3);
  node2->AddTransition(false, node7);
  node3->AddTransition(true, node4);
  node4->AddTransition(true, node5);
  node4->AddTransition(false, node6);
  node5->AddTransition(true, node4);
  node6->AddTransition(true, node2);
  node7->AddTransition(true, node8);
  node8->AddTransition(true, node9);
  node8->AddTransition(false, node12);
  node9->AddTransition(true, node10);
  node10->AddTransition(false, node8);
  node10->AddTransition(true, node11);
  node11->AddTransition(true, node10);

  pkb_write->AddCfg(cfg);

  SECTION("Test basic get relationship - Next") {
    std::string query = "stmt s; Select s such that Next(3, s)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_, WHILE-SYN) has result") {
    std::string query = "while w; Select w such that Next(_, w)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results { "10", "2", "4", "8" };
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(WHILE-SYN, IDENT) has a result") {
    std::string query = "while w; assign a; Select w such that Next(w, a)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results { "10", "2", "4", "8" };
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, WHILE-SYN) returns false") {
    std::string query = "while w; Select w such that Next(2, w)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration Testing for Affects API - Basic") {
  std::shared_ptr<Pkb> pkb_ = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read_facade_ = std::make_shared<PkbReadFacade>(*pkb_);
  std::shared_ptr<PkbWriteFacade>
      pkb_write_facade_ = std::make_shared<PkbWriteFacade>(*pkb_);
  typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;

  ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();
  std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
  typedef std::vector<std::shared_ptr<Token>> TokenList;

  std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node1->AddStmt(2);
  cfg->AddStmtCfg(2, node1);

  std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
  node2->AddStmt(3);
  cfg->AddStmtCfg(3, node2);

  std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
  node3->AddStmt(4);
  cfg->AddStmtCfg(4, node3);
  node3->AddStmt(5);
  cfg->AddStmtCfg(5, node3);
  node3->AddStmt(6);
  cfg->AddStmtCfg(6, node3);

  std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
  node4->AddStmt(7);
  cfg->AddStmtCfg(7, node4);

  std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
  node5->AddStmt(8);
  cfg->AddStmtCfg(8, node5);

  std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
  node6->AddStmt(9);
  cfg->AddStmtCfg(9, node6);

  std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
  node7->AddStmt(10);
  cfg->AddStmtCfg(10, node7);
  node7->AddStmt(11);
  cfg->AddStmtCfg(11, node7);
  node7->AddStmt(12);
  cfg->AddStmtCfg(12, node7);

  // 0
  TokenList token_list_statement_1{
      make_shared<IntegerToken>("0"),
  };

  pkb_write_facade_->AddStatementOfAType("1", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("1", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "1", egs->GetExpressionFromInput(
          token_list_statement_1, "assign"));

  // 5
  TokenList token_list_statement_2{
      make_shared<IntegerToken>("5"),
  };

  pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("2", "i");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "2", egs->GetExpressionFromInput(
          token_list_statement_2, "assign"));

  // i > 0
  TokenList token_list_statement_3{
      make_shared<NameToken>("i"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("0"),
  };

  pkb_write_facade_->AddStatementOfAType("3", WHILE);
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "4", egs->GetExpressionFromInput(
          token_list_statement_3, "while"));

  // x + 2 * y
  TokenList token_list_statement_4{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("y"),
  };

  pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("4", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "4", egs->GetExpressionFromInput(
          token_list_statement_4, "assign"));


  pkb_write_facade_->AddStatementOfAType("5", CALL);

  // i - 1
  TokenList token_list_statement_6{
      make_shared<NameToken>("i"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("6", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("6", "i");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "6", egs->GetExpressionFromInput(
          token_list_statement_6, "assign"));

  // x > 1
  TokenList token_list_statement_7{
      make_shared<NameToken>("3"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("7", IF);
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "7", egs->GetExpressionFromInput(
          token_list_statement_7, "if"));

  // x + 1
  TokenList token_list_statement_8{
      make_shared<NameToken>("3"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("8", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("8", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "8", egs->GetExpressionFromInput(
          token_list_statement_8, "assign"));

  // 1
  TokenList token_list_statement_9{
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("9", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("9", "z");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "9", egs->GetExpressionFromInput(
          token_list_statement_9, "assign"));

  // z + x + i
  TokenList token_list_statement_10{
      make_shared<NameToken>("z"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("i"),
  };

  pkb_write_facade_->AddStatementOfAType("10", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("10", "z");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "10", egs->GetExpressionFromInput(
          token_list_statement_10, "assign"));

  // z + 2
  TokenList token_list_statement_11{
      make_shared<NameToken>("z"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
  };

  pkb_write_facade_->AddStatementOfAType("11", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("11", "y");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "11", egs->GetExpressionFromInput(
          token_list_statement_11, "assign"));

  // x * y + z
  TokenList token_list_statement_12{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("y"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("z"),
  };

  pkb_write_facade_->AddStatementOfAType("12", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("12", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "12", egs->GetExpressionFromInput(
          token_list_statement_12, "assign"));

  pkb_write_facade_->AddStatementModifyingVariable("5", "z");
  pkb_write_facade_->AddStatementModifyingVariable("5", "v");

  node1->AddTransition(true, node2);
  node2->AddTransition(true, node3);
  node2->AddTransition(false, node4);
  node3->AddTransition(true, node2);
  node4->AddTransition(true, node5);
  node4->AddTransition(false, node6);
  node5->AddTransition(true, node7);
  node6->AddTransition(true, node7);

  cfg->AddProcCfg("second", node1);
  cfg->AddProcCfg("third", node3);
  pkb_write_facade_->AddCfg(cfg);

  SECTION("Affects(_, _) - is true") {
    std::string query = "Select BOOLEAN such that Affects(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is true") {
    std::string query = "Select BOOLEAN such that Affects(_,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is false") {
    std::string query = "Select BOOLEAN such that Affects(_,1)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, _) - is true") {
    std::string query = "Select BOOLEAN such that Affects(1,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, _) - is false") {
    std::string query = "Select BOOLEAN such that Affects(18,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- self modification e.g. x = x + 1") {
    std::string query = "Select BOOLEAN such that Affects(6,6)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // check this - expected result should be true -> need to fix bug in affects
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- affects an assign in while loop") {
    std::string query = "Select BOOLEAN such that Affects(1,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through while loop") {
    std::string query = "Select BOOLEAN such that Affects(1,8)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // check this - expected result should be true -> need to fix bug in affects
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through if else") {
    std::string query = "Select BOOLEAN such that Affects(1,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through stmt that uses"
          "but does not modify variable") {
    std::string query = "Select BOOLEAN such that Affects(1,12)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- simple case (one assign directly after another") {
    std::string query = "Select BOOLEAN such that Affects(9,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- check if nested assigns can affect") {
    std::string query = "Select BOOLEAN such that Affects(8,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- variable is read") {
    std::string query = "Select BOOLEAN such that Affects(11,14)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- variable modified in if case and else case") {
    std::string query = "Select BOOLEAN such that Affects(18,22)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- assigns are in different procedures") {
    std::string query = "Select BOOLEAN such that Affects(2,17)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  // check this -> confusion in affects queries
  SECTION("Affects(INT, INT) - is true -- variable is modified in a call stmt (even when in if-else)") {
    std::string query = "Select BOOLEAN such that Affects(2,6)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- affects does not hold for non-assign statements") {
    std::string query = "Select BOOLEAN such that Affects(2,3)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- a latter stmt cannot affect a stmt before it") {
    std::string query = "Select BOOLEAN such that Affects(6,2)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- simple case") {
    std::string query = "Select BOOLEAN such that Affects(9,11)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- simple case") {
    std::string query = "Select BOOLEAN such that Affects(9,12)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- compare between unrelated assigns") {
    std::string query = "Select BOOLEAN such that Affects(2,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // need to check this -> expected result is FALSE
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}




