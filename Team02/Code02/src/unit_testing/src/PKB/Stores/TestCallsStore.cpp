#include <catch.hpp>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "PKB/Stores/CallsStore.h"
#include "PKB/Types/PkbTypes.h"

TEST_CASE("Testcases for Calls Store") {
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<std::pair<Procedure, Procedure>, PairHasherUtil::hash_pair> ProcedureProcedurePairSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::unordered_set<std::pair<StatementNumber, Procedure>, PairHasherUtil::hash_pair>
      StatementNumberProcedurePairSet;

  SECTION("Empty Calls Store") {
    auto calls_store = new CallsStore();

    REQUIRE(calls_store->HasCallsRelation() == false);
    REQUIRE(calls_store->HasCallsRelation("caller procedure", "callee procedure") == false);

    REQUIRE(calls_store->GetCallsPairs() == ProcedureProcedurePairSet({}));

    REQUIRE(calls_store->HasCallsStarRelation() == false);
    REQUIRE(calls_store->HasCallsStarRelation("caller_procedure", "callee_procedure") == false);

    REQUIRE(calls_store->GetCallsStarPairs() == ProcedureProcedurePairSet({}));

    REQUIRE(calls_store->HasCallsStarRelation("procedure_name") == false);
    REQUIRE(calls_store->HasCallsStarRelationBy("procedure_name") == false);

    REQUIRE(calls_store->GetCallStatementsFromProcedure("procedure_name") == StatementNumberSet({}));

    REQUIRE(calls_store->GetCallStatementToProcedurePairs() == StatementNumberProcedurePairSet({}));
  }

  SECTION("Independent Calls without any Transitive Relationship") {
    auto calls_store = new CallsStore();

    calls_store->AddCallsRelation("caller_procedure1", "callee_procedure1");
    calls_store->AddCallsRelation("caller_procedure2", "callee_procedure2");
    calls_store->AddCallStatementToProcedure("4", "procedure3");
    calls_store->AddCallStatementToProcedure("10", "procedure4");

    REQUIRE(calls_store->HasCallsRelation() == true);
    REQUIRE(calls_store->HasCallsRelation("caller_procedure1", "callee_procedure1") == true);
    REQUIRE(calls_store->HasCallsRelation("caller_procedure2", "callee_procedure2") == true);

    REQUIRE_FALSE(calls_store->HasCallsRelation("caller_procedure1", "callee_procedure2") == true);
    REQUIRE_FALSE(calls_store->HasCallsRelation("caller_procedure2", "callee_procedure1") == true);

    REQUIRE(calls_store->GetCallsPairs() == ProcedureProcedurePairSet({
                                                                          std::make_pair("caller_procedure1",
                                                                                         "callee_procedure1"),
                                                                          std::make_pair("caller_procedure2",
                                                                                         "callee_procedure2")
                                                                      }));

    REQUIRE(calls_store->GetCallStatementsFromProcedure("procedure3") == StatementNumberSet({"4"}));

    REQUIRE(calls_store->GetCallStatementsFromProcedure("procedure4") == StatementNumberSet({"10"}));

    REQUIRE(calls_store->GetCallStatementToProcedurePairs() ==
        StatementNumberProcedurePairSet({std::make_pair("4", "procedure3"), std::make_pair("10", "procedure4")}));
  }

  SECTION("Test CallsStar Relation") {
    auto calls_star_store = new CallsStore();

    calls_star_store->AddCallsRelation("proc1", "proc2");
    calls_star_store->AddCallsRelation("proc1", "proc3");
    calls_star_store->AddCallsRelation("proc1", "proc4");
    calls_star_store->AddCallsRelation("proc4", "proc5");
    calls_star_store->AddCallsRelation("proc5", "proc6");
    calls_star_store->AddCallsRelation("proc5", "proc7");
    calls_star_store->AddCallsRelation("proc5", "proc8");
    calls_star_store->AddCallsRelation("proc5", "proc9");
    calls_star_store->AddCallsRelation("proc10", "proc11");
    calls_star_store->AddCallsRelation("proc10", "proc12");
    calls_star_store->AddCallsRelation("proc12", "proc13");

    calls_star_store->AddCallsStarRelation();

    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc2") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc3") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc4") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4", "proc5") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc5", "proc6") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc5", "proc7") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc5", "proc8") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc5", "proc9") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc10", "proc11") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc10", "proc12") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc12", "proc13") == true);

    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc5") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc6") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc7") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc8") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc1", "proc9") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4", "proc6") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4", "proc7") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4", "proc8") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4", "proc9") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc10", "proc13") == true);

    REQUIRE(calls_star_store->HasCallsStarRelation() == true);

    REQUIRE_FALSE(calls_star_store->HasCallsStarRelation("proc1") == true);

    REQUIRE(calls_star_store->HasCallsStarRelation("proc2") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc3") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc4") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc5") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc6") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc7") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc8") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc9") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc11") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc12") == true);
    REQUIRE(calls_star_store->HasCallsStarRelation("proc13") == true);

    REQUIRE(calls_star_store->HasCallsStarRelationBy("proc1") == true);
    REQUIRE(calls_star_store->HasCallsStarRelationBy("proc4") == true);
    REQUIRE(calls_star_store->HasCallsStarRelationBy("proc5") == true);
    REQUIRE(calls_star_store->HasCallsStarRelationBy("proc10") == true);
    REQUIRE(calls_star_store->HasCallsStarRelationBy("proc12") == true);
    REQUIRE_FALSE(calls_star_store->HasCallsStarRelationBy("proc2") == true);

    REQUIRE(calls_star_store->GetCallsStarPairs() == ProcedureProcedurePairSet({
                                                                                   std::make_pair("proc1", "proc2"),
                                                                                   std::make_pair("proc1", "proc3"),
                                                                                   std::make_pair("proc1", "proc4"),
                                                                                   std::make_pair("proc4", "proc5"),
                                                                                   std::make_pair("proc5", "proc6"),
                                                                                   std::make_pair("proc5", "proc7"),
                                                                                   std::make_pair("proc5", "proc8"),
                                                                                   std::make_pair("proc5", "proc9"),
                                                                                   std::make_pair("proc10", "proc11"),
                                                                                   std::make_pair("proc10", "proc12"),
                                                                                   std::make_pair("proc12", "proc13"),
                                                                                   std::make_pair("proc1", "proc5"),
                                                                                   std::make_pair("proc1", "proc6"),
                                                                                   std::make_pair("proc1", "proc7"),
                                                                                   std::make_pair("proc1", "proc8"),
                                                                                   std::make_pair("proc1", "proc9"),
                                                                                   std::make_pair("proc4", "proc6"),
                                                                                   std::make_pair("proc4", "proc7"),
                                                                                   std::make_pair("proc4", "proc8"),
                                                                                   std::make_pair("proc4", "proc9"),
                                                                                   std::make_pair("proc10", "proc13")
                                                                               }));
  }

  SECTION("Dependent Calls with Single Transitive Relationship") {
    auto calls_store = new CallsStore();

    calls_store->AddCallsRelation("proc1", "proc2");
    calls_store->AddCallsRelation("proc1", "proc3");
    calls_store->AddCallsRelation("proc3", "proc4");

    REQUIRE(calls_store->HasCallsRelation("proc1", "proc2") == true);
    REQUIRE(calls_store->HasCallsRelation("proc1", "proc3") == true);
    REQUIRE(calls_store->HasCallsRelation("proc3", "proc4") == true);

    REQUIRE(calls_store->HasCallsRelation() == true);

    REQUIRE(calls_store->GetCallsPairs() == ProcedureProcedurePairSet({
                                                                          std::make_pair("proc1", "proc2"),
                                                                          std::make_pair("proc1", "proc3"),
                                                                          std::make_pair("proc3", "proc4")
                                                                      }));
  }

  SECTION("Test OneToMany Calls Relation with statements and procedure") {
    auto calls_store = new CallsStore();

    calls_store->AddCallStatementToProcedure("4", "proc1");
    calls_store->AddCallStatementToProcedure("5", "proc1");
    calls_store->AddCallStatementToProcedure("6", "proc2");
    calls_store->AddCallStatementToProcedure("7", "proc2");
    calls_store->AddCallStatementToProcedure("8", "proc3");
    calls_store->AddCallStatementToProcedure("9", "proc3");

    REQUIRE(calls_store->GetCallStatementsFromProcedure("proc1") == StatementNumberSet({"4", "5"}));

    REQUIRE(calls_store->GetCallStatementsFromProcedure("proc2") == StatementNumberSet({"6", "7"}));

    REQUIRE(calls_store->GetCallStatementsFromProcedure("proc3") == StatementNumberSet({"8", "9"}));

    REQUIRE(calls_store->GetCallStatementToProcedurePairs() ==
        StatementNumberProcedurePairSet({
                                            std::make_pair("4", "proc1"),
                                            std::make_pair("5", "proc1"),
                                            std::make_pair("6", "proc2"),
                                            std::make_pair("7", "proc2"),
                                            std::make_pair("8", "proc3"),
                                            std::make_pair("9", "proc3")
                                        }));
  }
}
