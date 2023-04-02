#include "catch.hpp"

#include <memory>

#include "core/model/Expression.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Pkb.h"
#include "QPS/Qps.h"

TEST_CASE("Check if QPS works with Pkb for basic operations") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);

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

  pkb_write->AddStatementOfAType("1", READ);
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementOfAType("3", IF);
  pkb_write->AddStatementOfAType("4", PRINT);
  pkb_write->AddStatementOfAType("5", WHILE);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", PRINT);

  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");
  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");

  pkb_write->AddFollowsRelation("1", "2");
  pkb_write->AddFollowsRelation("2", "3");

  pkb_write->AddFollowsStarRelation();

  pkb_write->AddParentRelation("3", "4");
  pkb_write->AddParentRelation("3", "5");
  pkb_write->AddParentRelation("5", "6");

  pkb_write->AddParentStarRelation();

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

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- both special case") {
    QueryString query = "print p; read r; Select p with p.varName = r.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- both special case (swap args)") {
    QueryString query = "print p; read r; Select p with r.varName = p.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result") {
    QueryString
        query = "stmt s; constant c; Select s.stmt# with s.stmt# = c.value";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result (swap args)") {
    QueryString
        query = "stmt s; constant c; Select s.stmt# with c.value = s.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName") {
    QueryString query =
        "print pn; procedure proc; Select pn with pn.varName = proc.procName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName -- swap args") {
    QueryString query =
        "print pn; procedure proc; Select pn with proc.procName = pn.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- does not return result") {
    QueryString query = "print p; read r; Select r with p.stmt# = r.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    QueryString query = "print p; Select p.stmt# with p.varName=\"x\"";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return result") {
    QueryString query = "print p; Select p with 4=p.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    QueryString query = "print p; Select p.varName with p.stmt#=4";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return none ") {
    QueryString query = "print p; Select p with p.stmt#=1";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get procedure") {
    QueryString query = "procedure p; Select p";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"test"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get variable") {
    QueryString query = "variable v; Select v";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"test", "x", "y"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get procedure") {
    QueryString query = "constant c; Select c";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"0", "1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get statements") {
    QueryString query = "stmt s; Select s";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1", "2", "3", "4", "5", "6", "7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get assign statements") {
    QueryString query = "assign s; Select s";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"2", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get read statements") {
    QueryString query = "read r; Select r";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get print statements") {
    QueryString query = "print p; Select p";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4", "7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get if statements") {
    QueryString query = "if ifs; Select ifs";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get while statements") {
    QueryString query = "while w; Select w";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows") {
    QueryString query = "stmt s; Select s such that Follows(s, 2)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows*") {
    QueryString query = "stmt s; Select s such that Follows*(s, 2)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent") {
    QueryString query = "stmt s; Select s such that Parent(s, 4)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent*") {
    QueryString query = "stmt s; Select s such that Parent*(s, 4)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Uses") {
    QueryString query = "variable v; Select v such that Uses(2, v)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Modifies") {
    QueryString query = "variable v; Select v such that Modifies(1, v)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Test case of empty relationship stores") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("test");

  pkb_write->AddStatementOfAType("1", READ);
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementOfAType("3", IF);
  pkb_write->AddStatementOfAType("4", PRINT);
  pkb_write->AddStatementOfAType("5", WHILE);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", PRINT);
  pkb_write->AddStatementOfAType("8", CALL);

  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");

  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");

  SECTION("Calls(_,_)") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_)") {
    QueryString query = "procedure p; Select p such that Calls(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN)") {
    QueryString query = "procedure p; Select p such that Calls(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,_)") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_)") {
    QueryString query = "procedure p; Select p such that Calls*(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN)") {
    QueryString query = "procedure p; Select p such that Calls*(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Follows(_,_)") {
    QueryString query = "constant c; Select c.value such that Follows(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Parent(_,_)") {
    QueryString query = "assign a; Select a.stmt# such that Parent(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

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
    QueryString query =
        "procedure p,p1,p2,p3,p4; "
        "Select <p1,p2,p3.procName,p4> such that Calls(p1,p2) and Calls(p2,p3) and Calls(p3,p4)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1 proc2 proc3 proc4", "proc1 proc2 proc5 proc6",
                         "proc2 proc5 proc6 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,_) is true") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is true") {
    QueryString
        query = "procedure p; Select <p.procName> such that Calls(_,\"proc5\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is false") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls (_,\"proc1\"  )   ";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is true") {
    QueryString query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls  (\"proc1\",   _)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is false") {
    QueryString query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls(\"proc8\",_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is true") {
    QueryString
        query = "procedure p; Select p such that Calls(\"proc1\",\"proc2\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is false") {
    QueryString query =
        "procedure p; Select p .procName such that Calls(\"proc3    \",\"       proc2\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_) has result") {
    QueryString query = "procedure p; Select p. procName such that Calls(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls(p, \"      proc2       \")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has no result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls(p, \"proc8\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,PROC-SYN) has result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with q.procName = \"proc6\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc5"};
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls(PROC-SYN,PROC-SYN) has no result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with p.procName = \"proc4\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN) has result") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,PROC-SYN) has result") {
    QueryString
        query = "procedure p; Select p.procName such that Calls(\"proc2\",p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc3", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause") {
    // Select procedures that call procedures that are callers
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select p1 such that Calls(p1,p2) and Calls(p2,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1", "proc2", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls*") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

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
    QueryString query = "procedure p; Select p.procName such that Calls*(p,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(p,p) should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls(p,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls('proc1','proc1') should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls(\"proc1\",\"proc1\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*('proc1','proc1') should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls*(\"proc1\",\"proc1\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,_) is true") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is true") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc4\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is false") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc8\"  )   ";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is true") {
    QueryString query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls*  (\"proc2\",   _)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is false") {
    QueryString query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls*(\"proc7\",_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is true") {
    QueryString
        query = "procedure p; Select p such that Calls*(\"proc2\",\"proc7\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is false") {
    QueryString query =
        "procedure p; Select p .procName such that Calls*(\"proc4  \",\"       proc7\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_) has result") {
    QueryString query = "procedure p; Select p. procName such that Calls*(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls*(p, \"      proc7       \")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1", "proc2", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has no result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls*(p, \"proc8\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,PROC-SYN) has result") {
    QueryString query =
        "procedure p; procedure q; Select q.procName such that Calls*(p,q) with p.procName = \"proc2\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls*(PROC-SYN,PROC-SYN) has no result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls*(p,q) with q.procName = \"proc1\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN) has result") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,PROC-SYN) has result") {
    QueryString
        query = "procedure p; Select p.procName such that Calls*(\"proc5\",p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- indirect calls only") {
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3> such that Calls(p1,p2) and Calls*(p2,p3)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc3", "proc1 proc4", "proc1 proc5", "proc1 proc6",
         "proc1 proc7", "proc2 proc4", "proc2 proc6",
         "proc2 proc7", "proc5 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- test transitive") {
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3.procName> such that Calls(p1,p2) and Calls*(p2,p3) and Calls*(p3,p4)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc3", "proc1 proc5", "proc1 proc6", "proc2 proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Next - Basic") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  CfgPtr cfg = std::make_shared<Cfg>();

  CfgNodePtr node1 = std::make_shared<CfgNode>();
  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node1->AddStmt(2);
  cfg->AddStmtCfg(2, node1);

  CfgNodePtr node2 = std::make_shared<CfgNode>();
  node2->AddStmt(3);
  cfg->AddStmtCfg(3, node2);
  node2->AddStmt(4);
  cfg->AddStmtCfg(4, node2);

  CfgNodePtr node3 = std::make_shared<CfgNode>();
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
    QueryString query = "stmt s; Select s.stmt# such that Next(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is true") {
    QueryString query = "stmt s; Select <s.stmt#> such that Next(_,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is false") {
    QueryString query = "stmt s; Select <s.stmt#> such that Next (_,1 )";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is true") {
    QueryString query =
        "stmt s1; stmt s2; Select <s1.stmt#, s1.stmt#> such that Next (1,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"1 1", "2 2", "3 3", "4 4", "5 5", "6 6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is false") {
    QueryString query =
        "stmt s1; stmt s2; Select <s1.stmt#, s2.stmt#> such that Next (6,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is true") {
    QueryString query = "stmt s; Select s such that Next(1,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is false") {
    QueryString query = "stmt s; Select s .stmt# such that Next(3,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
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
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  CfgPtr cfg = std::make_shared<Cfg>();

  CfgNodePtr node1 = std::make_shared<CfgNode>();
  CfgNodePtr node2 = std::make_shared<CfgNode>();
  CfgNodePtr node3 = std::make_shared<CfgNode>();
  CfgNodePtr node4 = std::make_shared<CfgNode>();
  CfgNodePtr node5 = std::make_shared<CfgNode>();
  CfgNodePtr node6 = std::make_shared<CfgNode>();
  CfgNodePtr node7 = std::make_shared<CfgNode>();
  CfgNodePtr node8 = std::make_shared<CfgNode>();
  CfgNodePtr node9 = std::make_shared<CfgNode>();
  CfgNodePtr node10 = std::make_shared<CfgNode>();
  CfgNodePtr node11 = std::make_shared<CfgNode>();
  CfgNodePtr node12 = std::make_shared<CfgNode>();

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
    QueryString query = "stmt s; Select s such that Next(3, s)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_, WHILE-SYN) has result") {
    QueryString query = "while w; Select w such that Next(_, w)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"10", "2", "4", "8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(WHILE-SYN, IDENT) has a result") {
    QueryString query = "while w; assign a; Select w such that Next(w, a)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"10", "2", "4", "8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, WHILE-SYN) returns false") {
    QueryString query = "while w; Select w such that Next(2, w)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }
}


