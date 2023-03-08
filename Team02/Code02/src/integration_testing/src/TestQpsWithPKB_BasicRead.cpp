#include "catch.hpp"

#include <memory>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/PKB.h"
#include "QPS/Qps.h"
#include "PKB/Stores/CallsStore.h"

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

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- both special case") {
    std::string query = "print p; read r; Select p with p.varName = r.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- both special case (swap args)") {
    std::string query = "print p; read r; Select p with r.varName = p.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- returns result") {
    std::string query = "stmt s; constant c; Select s.stmt# with s.stmt# = c.value";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- returns result (swap args)") {
    std::string query = "stmt s; constant c; Select s.stmt# with c.value = s.stmt#";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName") {
    std::string query = "print pn; procedure proc; Select pn with pn.varName = proc.procName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName -- swap args") {
    std::string query = "print pn; procedure proc; Select pn with proc.procName = pn.varName";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- does not return result") {
    std::string query = "print p; read r; Select r with p.stmt# = r.stmt#";
    std::list<std::string> results;

    Qps::ProcessQuery(query, results, pkb_read);

    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship -- with attr_ref = int -- select varName from print") {
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


  SECTION("Test basic get relationship -- with attr_ref = int -- select varName from print") {
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

    std::list<std::string> expected_results{"test","x", "y"};
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
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade> pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

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
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade> pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

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


  SECTION("Calls(_,_) is true") {
    std::string query = "procedure p; Select p.procName such that Calls(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is true") {
    std::string query = "procedure p; Select <p.procName> such that Calls(_,\"proc5\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is false") {
    std::string query = "procedure p; Select <p.procName> such that Calls (_,\"proc1\"  )   ";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is true") {
    std::string query = "procedure p; procedure q       ; Select   <p. procName, q .procName > such that Calls  (\"proc1\",   _)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4", "proc5 proc5", "proc6 proc 6", "proc7 proc 7", "proc8 proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is false") {
    std::string query = "procedure p; procedure q; Select <p.procName, q.procName> such that Calls(\"proc8\",_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is true") {
    std::string query = "procedure p; Select p such that Calls(\"proc1\",\"proc2\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is false") {
    std::string query = "procedure p; Select p .procName such that Calls(\"proc3    \",\"       proc2\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_) has result") {
    std::string query = "procedure p; Select p. procName such that Calls(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has result") {
    std::string query = "procedure p; Select p  . procName such that Calls(p, \"      proc2       \")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has no result") {
    std::string query = "procedure p; Select p  . procName such that Calls(p, \"proc8\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,PROC-SYN) has result") {
    std::string query = "procedure p; procedure q; Select p.procName such that Calls(p,q) with q.procName = \"proc6\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc5"};
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls(PROC-SYN,PROC-SYN) has no result") {
    std::string query = "procedure p; procedure q; Select p.procName such that Calls(p,q) with p.procName = \"proc4\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls(\"proc2\",p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc3", "proc5"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause") {
    //Select procedures that call procedures that are callers
    std::string query = "procedure p,p1,p2,p3,p4; Select p1 such that Calls(p1,p2) and Calls(p2,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc5", "proc6"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- test transitive") {
    //Select procedures that call procedures that are callers
    std::string query = "procedure p,p1,p2,p3,p4; Select <p1,p2,p3.procName,p4> such that Calls(p1,p2) and Calls(p2,p3) and Calls(p3,p4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1 proc2 proc3 proc4", "proc2 proc5 proc6 proc7"};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls*") {
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  std::shared_ptr<PkbWriteFacade> pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

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


  SECTION("Calls*(_,_) is true") {
    std::string query = "procedure p; Select p.procName such that Calls*(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is true") {
    std::string query = "procedure p; Select <p.procName> such that Calls*(_,\"proc4\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is false") {
    std::string query = "procedure p; Select <p.procName> such that Calls*(_,\"proc8\"  )   ";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is true") {
    std::string query = "procedure p; procedure q       ; Select   <p. procName, q .procName > such that Calls*  (\"proc2\",   _)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4", "proc5 proc5", "proc6 proc 6", "proc7 proc 7", "proc8 proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is false") {
    std::string query = "procedure p; procedure q; Select <p.procName, q.procName> such that Calls*(\"proc7\",_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is true") {
    std::string query = "procedure p; Select p such that Calls*(\"proc2\",\"proc7\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7", "proc8"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is false") {
    std::string query = "procedure p; Select p .procName such that Calls*(\"proc4  \",\"       proc7\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_) has result") {
    std::string query = "procedure p; Select p. procName such that Calls*(p,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has result") {
    std::string query = "procedure p; Select p  . procName such that Calls*(p, \"      proc7       \")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1", "proc2", "proc5", "proc6"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has no result") {
    std::string query = "procedure p; Select p  . procName such that Calls*(p, \"proc8\")";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,PROC-SYN) has result") {
    std::string query = "procedure p; procedure q; Select q.procName such that Calls*(p,q) with p.procName = \"proc2\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc3", "proc5", "proc4", "proc6", "proc7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls*(PROC-SYN,PROC-SYN) has no result") {
    std::string query = "procedure p; procedure q; Select p.procName such that Calls*(p,q) with q.procName = \"proc1\"";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls*(_,p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,PROC-SYN) has result") {
    std::string query = "procedure p; Select p.procName such that Calls*(\"proc5\",p)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc6", "proc7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- indirect calls only") {
    std::string query = "procedure p,p1,p2,p3,p4; Select <p1,p3> such that Calls(p1,p2) and Calls*(p2,p3)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1 proc3", "proc1 proc4", "proc1 proc5", "proc1 proc6", "proc1 proc7", "proc2 proc4", "proc2 proc6","proc2 proc7", "proc5 proc7"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- test transitive") {
    std::string query = "procedure p,p1,p2,p3,p4; Select <p1,p3.procName> such that Calls(p1,p2) and Calls*(p2,p3) and Calls*(p3,p4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read);
    std::list<std::string> expected_results{"proc1 proc3", "proc1 proc5", "proc1 proc6", "proc2 proc6"};
    REQUIRE(results == expected_results);
  }
}