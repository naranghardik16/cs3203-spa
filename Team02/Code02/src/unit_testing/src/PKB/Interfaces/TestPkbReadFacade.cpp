#include <catch.hpp>

#include <string>
#include <unordered_set>

#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "ExpressionGeneratorStub/ExpressionGeneratorStub.h"

TEST_CASE("Test UsesProcedure API") {
    SECTION("Testing UsesProcedure API") {
      Pkb pkb_ = Pkb();
      PkbReadFacade *pkb_read_facade_;
      PkbWriteFacade *pkb_write_facade_;

      pkb_read_facade_ = new PkbReadFacade(pkb_);
      pkb_write_facade_ = new PkbWriteFacade(pkb_);

      pkb_write_facade_->AddProcedure("proc1");
      pkb_write_facade_->AddProcedure("proc2");
      pkb_write_facade_->AddProcedure("proc3");
      pkb_write_facade_->AddProcedure("proc4");

      pkb_write_facade_->AddProcedureUsingVariable("proc1", "x");
      pkb_write_facade_->AddProcedureUsingVariable("proc1", "y");
      pkb_write_facade_->AddProcedureUsingVariable("proc1", "z");
      pkb_write_facade_->AddProcedureUsingVariable("proc2", "l");
      pkb_write_facade_->AddProcedureUsingVariable("proc2", "m");
      pkb_write_facade_->AddProcedureUsingVariable("proc2", "n");
      pkb_write_facade_->AddProcedureUsingVariable("proc3", "p");
      pkb_write_facade_->AddProcedureUsingVariable("proc3", "q");
      pkb_write_facade_->AddProcedureUsingVariable("proc3", "r");
      pkb_write_facade_->AddProcedureUsingVariable("proc4", "a");
      pkb_write_facade_->AddProcedureUsingVariable("proc4", "b");
      pkb_write_facade_->AddProcedureUsingVariable("proc4", "c");

      REQUIRE(pkb_read_facade_->GetProceduresThatUse() == std::unordered_set<PkbTypes::PROCEDURE>(
                                                              {"proc1", "proc2", "proc3", "proc4"}));
      REQUIRE(pkb_read_facade_->GetVariablesUsedByProcedure("proc1") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                              {"x", "y", "z"}));
      REQUIRE(pkb_read_facade_->GetVariablesUsedByProcedure("proc2") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                            {"l", "m", "n"}));
      REQUIRE(pkb_read_facade_->GetVariablesUsedByProcedure("proc3") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                            {"p", "q", "r"}));
      REQUIRE(pkb_read_facade_->GetVariablesUsedByProcedure("proc4") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                            {"a", "b", "c"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("x") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                              {"proc1"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("y") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc1"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("z") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc1"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("l") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc2"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("m") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc2"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("n") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc2"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("p") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc3"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("q") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc3"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("r") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc3"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("a") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc4"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("b") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc4"}));
      REQUIRE(pkb_read_facade_->GetProceduresUsesVariable("c") == std::unordered_set<PkbTypes::PROCEDURE>(
                                                                      {"proc4"}));
      REQUIRE(pkb_read_facade_->HasUsesProcedureRelationship("proc1", "x") == true);
      REQUIRE_FALSE(pkb_read_facade_->GetUsesProcedureVariablePairs() ==
                    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>,
                                       PairHasherUtil::hash_pair>({std::make_pair("procedure", "bar"),
                                                                   std::make_pair("procedure", "x"),
                                                                   std::make_pair("procedure", "z")}));
    }
}

TEST_CASE("Testing PkbReadFacade") {
  SECTION("Testing Modifies API") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;

    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", IF);
    pkb_write_facade_->AddStatementOfAType("3", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);

    pkb_write_facade_->AddParentRelation("2", "3");
    pkb_write_facade_->AddParentRelation("2", "4");
    pkb_write_facade_->AddParentStarRelation();

    pkb_write_facade_->AddStatementModifyingVariable("1", "x");
    pkb_write_facade_->AddStatementModifyingVariable("3", "z");
    pkb_write_facade_->AddStatementModifyingVariable("4", "x");

    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("3") ==
        std::unordered_set<std::string>({"z"}));

    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("2") ==
        std::unordered_set<std::string>({"z", "x"}));

    REQUIRE(pkb_read_facade_->GetStatements() ==
        std::unordered_set<std::string>({"4", "2", "3", "1"}));

    REQUIRE(pkb_read_facade_->GetStatementsThatModify(STATEMENT) ==
        std::unordered_set<std::string>({"2", "3", "4", "1"}));

    REQUIRE(pkb_read_facade_->GetStatementsModifiesVariable("z", IF) ==
        std::unordered_set<std::string>({"2"}));
  }

  SECTION("Testing Modifies API") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;

    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", IF);
    pkb_write_facade_->AddStatementOfAType("3", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("5", PRINT);

    pkb_write_facade_->AddParentRelation("2", "3");
    pkb_write_facade_->AddParentRelation("2", "4");
    pkb_write_facade_->AddParentStarRelation();

    pkb_write_facade_->AddVariable("x");
    pkb_write_facade_->AddVariable("z");
    pkb_write_facade_->AddVariable("bar");

    pkb_write_facade_->AddConstant("2");

    pkb_write_facade_->AddProcedure("procedure");

    pkb_write_facade_->AddStatementModifyingVariable("1", "x");
    pkb_write_facade_->AddStatementModifyingVariable("3", "z");
    pkb_write_facade_->AddStatementModifyingVariable("4", "x");
    pkb_write_facade_->AddStatementUsingVariable("5", "bar");
    pkb_write_facade_->AddProcedureModifyingVariable("procedure", "bar");
    pkb_write_facade_->AddProcedureModifyingVariable("procedure", "x");
    pkb_write_facade_->AddProcedureModifyingVariable("procedure", "z");


    REQUIRE(pkb_read_facade_->GetVariables() == std::unordered_set<std::string>({"x", "z", "bar"}));
    REQUIRE(pkb_read_facade_->GetConstants() == std::unordered_set<std::string>({"2"}));
    REQUIRE(pkb_read_facade_->GetProcedures() == std::unordered_set<std::string>({"procedure"}));
    REQUIRE(pkb_read_facade_->GetPrintStatements() == std::unordered_set<std::string>({"5"}));
    REQUIRE(pkb_read_facade_->GetModifiesStatementVariablePairs(PRINT) == std::unordered_set<
        std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({}));
    REQUIRE(pkb_read_facade_->GetVariablesModifiedByProcedure("procedure") == std::unordered_set<
        std::string>({"bar", "x", "z"}));
    REQUIRE(pkb_read_facade_->GetProceduresThatModify() == std::unordered_set<std::string>({"procedure"}));
    REQUIRE(pkb_read_facade_->GetModifiesProcedureVariablePairs() ==
            std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>,
                PairHasherUtil::hash_pair>({std::make_pair("procedure", "bar"),
                                                           std::make_pair("procedure", "x"),
                                                           std::make_pair("procedure", "z")}));
    REQUIRE(pkb_read_facade_->GetProceduresModifiesVariable("bar") == std::unordered_set<std::string>
        ({"procedure"}));
  }

  SECTION("Test Calls API") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddCallsRelation("proc1", "proc2");
    pkb_write_facade_->AddCallsRelation("proc1", "proc3");
    pkb_write_facade_->AddCallsRelation("proc1", "proc4");
    pkb_write_facade_->AddCallsRelation("proc4", "proc5");
    pkb_write_facade_->AddCallsRelation("proc5", "proc6");
    pkb_write_facade_->AddCallsRelation("proc5", "proc7");
    pkb_write_facade_->AddCallsRelation("proc5", "proc8");
    pkb_write_facade_->AddCallsRelation("proc5", "proc9");
    pkb_write_facade_->AddCallsRelation("proc10", "proc11");
    pkb_write_facade_->AddCallsRelation("proc10", "proc12");
    pkb_write_facade_->AddCallsRelation("proc12", "proc13");
    pkb_write_facade_->AddCallsStarRelation();

    REQUIRE(pkb_read_facade_->GetAllCallsPairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc2"),
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc3"),
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc4"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc5"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc6"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc7"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc8"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc9"),
                                                          std::make_pair(
                                                              "proc10",
                                                              "proc11"),
                                                          std::make_pair(
                                                              "proc12",
                                                              "proc13"),
                                                          std::make_pair(
                                                              "proc10",
                                                              "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc1", "proc2"),
                                                          std::make_pair("proc1", "proc3"),
                                                          std::make_pair("proc1", "proc4"),
                                                          std::make_pair("proc4", "proc5"),
                                                          std::make_pair("proc5", "proc6"),
                                                          std::make_pair("proc5", "proc7"),
                                                          std::make_pair("proc5", "proc8"),
                                                          std::make_pair("proc5", "proc9"),
                                                          std::make_pair("proc10", "proc11"),
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
                                                          std::make_pair("proc10", "proc13"),
                                                          std::make_pair("proc10", "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc12") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc12",
                                                              "proc13")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc1") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc1", "proc2"),
                                                          std::make_pair("proc1", "proc3"),
                                                          std::make_pair("proc1", "proc4")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc4") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc4", "proc5")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc5") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc5", "proc6"),
                                                          std::make_pair("proc5", "proc7"),
                                                          std::make_pair("proc5", "proc8"),
                                                          std::make_pair("proc5", "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc10") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc10", "proc11"),
                                                          std::make_pair("proc10", "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc1") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc2"),
                                                       std::make_pair("proc1", "proc3"),
                                                       std::make_pair("proc1", "proc4"),
                                                       std::make_pair("proc1", "proc5"),
                                                       std::make_pair("proc1", "proc6"),
                                                       std::make_pair("proc1", "proc7"),
                                                       std::make_pair("proc1", "proc8"),
                                                       std::make_pair("proc1", "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc4") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc4", "proc5"),
                                                          std::make_pair("proc4", "proc6"),
                                                          std::make_pair("proc4", "proc7"),
                                                          std::make_pair("proc4", "proc8"),
                                                          std::make_pair("proc4", "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc5") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc5", "proc6"),
                                                       std::make_pair("proc5", "proc7"),
                                                       std::make_pair("proc5", "proc8"),
                                                       std::make_pair("proc5", "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc10") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc10", "proc11"),
                                                       std::make_pair("proc10", "proc13"),
                                                       std::make_pair("proc10", "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc12") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc12", "proc13")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc2") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc2")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc3") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc3")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc4") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc4")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc5") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc4", "proc5")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc6") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc5", "proc6")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc7") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc5", "proc7")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc8") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc5", "proc8")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc9") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc5", "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc11") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc10", "proc11")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc12") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc10", "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc13") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc12", "proc13")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc2") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc2")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc3") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc3")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc4") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({std::make_pair("proc1", "proc4")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc5") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc5"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc5")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc6") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc6"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc6"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc6")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc7") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc7"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc7"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc7")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc8") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc8"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc8"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc8")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc9") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc1",
                                                              "proc9"),
                                                          std::make_pair(
                                                              "proc4",
                                                              "proc9"),
                                                          std::make_pair(
                                                              "proc5",
                                                              "proc9")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc12") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc10",
                                                              "proc12")
                                                      }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc13") ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "proc10",
                                                              "proc13"),
                                                          std::make_pair(
                                                              "proc12",
                                                              "proc13")
                                                      }));

    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc2") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc3") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc4") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc4", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc10", "proc11") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc10", "proc12") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc12", "proc13") == true);

    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc2") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc3") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc4") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc11") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc12") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc12", "proc13") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc8") == true);

    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc13") == true);
  }

  SECTION("Test Next API - Complex CFG") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);
    node1->AddStmt(3);
    cfg->AddStmtCfg(3, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(4);
    cfg->AddStmtCfg(4, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg->AddStmtCfg(5, node3);

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(6);
    cfg->AddStmtCfg(6, node4);

    std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
    node5->AddStmt(7);
    cfg->AddStmtCfg(7, node5);

    std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
    node6->AddStmt(8);
    cfg->AddStmtCfg(8, node6);

    std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
    node7->AddStmt(9);
    cfg->AddStmtCfg(9, node7);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);
    pkb_write_facade_->AddStatementOfAType("7", READ);
    pkb_write_facade_->AddStatementOfAType("8", READ);
    pkb_write_facade_->AddStatementOfAType("9", READ);

    node1->AddTransition(true, node2);
    node2->AddTransition(true, node3);
    node3->AddTransition(true, node2);
    node2->AddTransition(false, node4);
    node4->AddTransition(false, node5);
    node4->AddTransition(true, node6);
    node6->AddTransition(true, node7);

    cfg->AddProcCfg("main", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);

    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE(pkb_read_facade_->HasNext("6") == true);
    REQUIRE(pkb_read_facade_->HasNext("8") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2"}));

    REQUIRE(pkb_read_facade_->GetNext("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"3"}));

    REQUIRE(pkb_read_facade_->GetNext("3", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4"}));

    REQUIRE(pkb_read_facade_->GetNext("8", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"9"}));

    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));

    REQUIRE(pkb_read_facade_->GetNextBy("3", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2"}));

    REQUIRE(pkb_read_facade_->GetNextBy("9", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8"}));

    REQUIRE(pkb_read_facade_->GetNextFirst(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "2", "3", "5", "4",
                                                        "6", "8"}));

    REQUIRE(pkb_read_facade_->GetNextSecond(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "3", "4", "5", "6",
                                                        "7", "8", "9"}));

    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("1", "2"),
                                                          std::make_pair("2", "3"),
                                                          std::make_pair("3", "4"),
                                                          std::make_pair("4", "5"),
                                                          std::make_pair("4", "6"),
                                                          std::make_pair("5", "4"),
                                                          std::make_pair("6", "7"),
                                                          std::make_pair("6", "8"),
                                                          std::make_pair("8", "9")
                                                      }));

    REQUIRE_FALSE(pkb_read_facade_->GetNextStarPairs(READ, READ) ==
            std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                               PairHasherUtil::hash_pair>({
                std::make_pair("1", "2"),
                std::make_pair("2", "3"),
                std::make_pair("3", "4"),
                std::make_pair("4", "5"),
                std::make_pair("4", "6"),
                std::make_pair("5", "4"),
                std::make_pair("6", "7"),
                std::make_pair("6", "8"),
                std::make_pair("8", "9")
            }));
  }

  SECTION("Test Next API - With Dummy Node") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

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

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(7);
    cfg->AddStmtCfg(7, node4);
    node4->AddStmt(8);
    cfg->AddStmtCfg(8, node4);

    std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();

    std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
    node6->AddStmt(9);
    cfg->AddStmtCfg(9, node6);
    node6->AddStmt(10);
    cfg->AddStmtCfg(10, node6);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);
    pkb_write_facade_->AddStatementOfAType("7", READ);
    pkb_write_facade_->AddStatementOfAType("8", READ);
    pkb_write_facade_->AddStatementOfAType("9", READ);
    pkb_write_facade_->AddStatementOfAType("10", READ);

    node1->AddTransition(true, node2);
    node1->AddTransition(false, node3);

    node2->AddTransition(true, node4);
    node3->AddTransition(true, node4);
    node4->AddTransition(true, node5);
    node5->AddTransition(true, node6);

    cfg->AddProcCfg("main", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("7", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);
    REQUIRE(pkb_read_facade_->IsNext("9", "10") == true);

    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE(pkb_read_facade_->HasNext("6") == true);
    REQUIRE(pkb_read_facade_->HasNext("7") == true);
    REQUIRE(pkb_read_facade_->HasNext("8") == true);
    REQUIRE(pkb_read_facade_->HasNext("9") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2"}));

    REQUIRE(pkb_read_facade_->GetNext("3", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4"}));

    REQUIRE(pkb_read_facade_->GetNext("5", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"6"}));

    REQUIRE(pkb_read_facade_->GetNext("7", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8"}));

    REQUIRE(pkb_read_facade_->GetNext("9", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"10"}));

    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));

    REQUIRE(pkb_read_facade_->GetNextBy("4", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"3"}));

    REQUIRE(pkb_read_facade_->GetNextBy("6", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"5"}));

    REQUIRE(pkb_read_facade_->GetNextBy("8", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"7"}));

    REQUIRE(pkb_read_facade_->GetNextBy("10", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"9"}));

    REQUIRE(pkb_read_facade_->GetNextFirst(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "2", "3", "5", "4",
                                                        "6", "7", "8", "9"}));

    REQUIRE(pkb_read_facade_->GetNextSecond(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "3", "4", "5", "6",
                                                        "7", "8", "9", "10"}));

    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("1", "2"),
                                                          std::make_pair("2", "3"),
                                                          std::make_pair("3", "4"),
                                                          std::make_pair("5", "6"),
                                                          std::make_pair("2", "5"),
                                                          std::make_pair("4", "7"),
                                                          std::make_pair("7", "8"),
                                                          std::make_pair("6", "7"),
                                                          std::make_pair("8", "9"),
                                                          std::make_pair("9", "10")
                                                      }));
  }

  SECTION("Test Next Star API - Complex CFG") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);
    node1->AddStmt(3);
    cfg->AddStmtCfg(3, node1);
    node1->AddStmt(4);
    cfg->AddStmtCfg(4, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(5);
    cfg->AddStmtCfg(5, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(6);
    cfg->AddStmtCfg(6, node3);
    node3->AddStmt(7);
    cfg->AddStmtCfg(7, node3);

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(8);
    cfg->AddStmtCfg(8, node4);

    std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
    node5->AddStmt(9);
    cfg->AddStmtCfg(9, node5);
    node5->AddStmt(10);
    cfg->AddStmtCfg(10, node5);

    std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
    node6->AddStmt(11);
    cfg->AddStmtCfg(11, node6);
    node6->AddStmt(12);
    cfg->AddStmtCfg(12, node6);

    std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
    node7->AddStmt(13);
    cfg->AddStmtCfg(13, node7);
    node7->AddStmt(14);
    cfg->AddStmtCfg(14, node7);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("3", CALL);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("5", IF);
    pkb_write_facade_->AddStatementOfAType("6", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("7", CALL);
    pkb_write_facade_->AddStatementOfAType("8", WHILE);
    pkb_write_facade_->AddStatementOfAType("9", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("10", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("11", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("12", CALL);
    pkb_write_facade_->AddStatementOfAType("13", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("14", CALL);

    node1->AddTransition(true, node2);
    node2->AddTransition(true, node3);
    node2->AddTransition(false, node4);
    node3->AddTransition(true, node7);
    node4->AddTransition(true, node5);
    node4->AddTransition(false, node6);
    node5->AddTransition(true, node4);
    node6->AddTransition(true, node7);

    cfg->AddProcCfg("Bumblebee", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->IsNextStar("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "3") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "4") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "5") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "6") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "7") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("1", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "4") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "5") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "6") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "7") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("2", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "5") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "6") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "7") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("3", "14") == true);
    REQUIRE_FALSE(pkb_read_facade_->IsNextStar("3", "2") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "5") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "6") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "7") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("4", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "7") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("5", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("6", "7") == true);
    REQUIRE_FALSE(pkb_read_facade_->IsNextStar("6", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("6", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("6", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("7", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("7", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "9") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("8", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("9", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "8") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "10") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "11") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("10", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("11", "12") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("11", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("11", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("12", "13") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("12", "14") == true);
    REQUIRE(pkb_read_facade_->IsNextStar("13", "14") == true);
    REQUIRE(pkb_read_facade_->HasNextStarRelationship() == true);
    REQUIRE(pkb_read_facade_->HasNextStar("1") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("2") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("3") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("4") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("5") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("6") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("7") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("8") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("9") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("10") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("11") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("12") == true);
    REQUIRE(pkb_read_facade_->HasNextStar("13") == true);
    REQUIRE_FALSE(pkb_read_facade_->HasNextStar("14") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("2") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("3") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("4") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("5") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("6") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("7") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("8") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("9") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("10") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("11") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("12") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("13") == true);
    REQUIRE(pkb_read_facade_->HasNextStarBy("14") == true);
    REQUIRE(pkb_read_facade_->GetNextStarFirst(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
        ({"2", "4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"3", "7", "12"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"2", "4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"3", "7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
                                                           "5"
                                                       }));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
                                                           "8"
                                                       }));
    REQUIRE(pkb_read_facade_->GetNextStar("1", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("1", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"2", "4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("1", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"3", "7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("1", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("1", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStar("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("2", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("2", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"3", "7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("2", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("2", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStar("3", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("3", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("3", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("3", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("3", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStar("4", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("4", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("4", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("4", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("4", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStar("5", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("5", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("5", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("5", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("5", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("6", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("6", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("6", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"7", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("6", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("6", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("7", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("7", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("7", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("7", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("7", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("8", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("8", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("8", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("8", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("8", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("9", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("9", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"10", "11", "13", "9"}));
    REQUIRE(pkb_read_facade_->GetNextStar("9", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("9", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("9", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("10", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("10", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("10", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("10", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("10", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("11", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("11", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("11", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("11", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("11", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("12", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("12", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"13"}));
    REQUIRE(pkb_read_facade_->GetNextStar("12", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("12", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("12", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {"14"}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));

    REQUIRE(pkb_read_facade_->GetNextStarBy("1", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("1", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("1", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("1", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("1", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("2", ASSIGN) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("2", CALL) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("2", WHILE) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("2", IF) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
            {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("3", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("3", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("3", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("3", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("3", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("4", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("4", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("4", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("4", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("4", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("5", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("5", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("5", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("5", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("5", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("6", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("6", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("6", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("6", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("6", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("7", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("7", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "6"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("7", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("7", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("7", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("8", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("8", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "9", "10"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("8", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("8", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("8", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("9", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("9", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "9", "10"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("9", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("9", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("9", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("10", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("10", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "9", "10"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("10", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("10", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("10", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("11", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("11", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "9", "10"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("11", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("11", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("11", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("12", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("12", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "9", "10", "11"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("12", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("12", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("12", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("13", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("13", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "6", "9", "10", "11"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("13", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3", "7", "12"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("13", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("13", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("14", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("14", ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"2", "4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("14", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"3", "7", "12"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("14", WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarBy("14", IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
                    {"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "4", "6", "9", "10", "11", "13"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"3", "7", "12"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarFirst(WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(ASSIGN)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "4", "13", "10", "11", "9", "6"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"3", "7", "12", "14"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(IF)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"5"}));
    REQUIRE(pkb_read_facade_->GetNextStarSecond(WHILE)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8"}));
    REQUIRE(pkb_read_facade_->GetNextStar("1", READ)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(pkb_read_facade_->GetNextStar("13", CALL)
                == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"14"}));
  }

  SECTION("Test Next API - Basic CFG") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

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

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);

    node1->AddTransition(true, node2);
    node1->AddTransition(false, node3);

    cfg->AddProcCfg("main", node1);
    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->HasNextRelationship() == true);
    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "5") == true);
    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE_FALSE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE_FALSE(pkb_read_facade_->HasNext("6") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2"}));

    REQUIRE(pkb_read_facade_->GetNext("3", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4"}));

    REQUIRE(pkb_read_facade_->GetNext("5", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"6"}));

    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1"}));

    REQUIRE(pkb_read_facade_->GetNextBy("4", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"3"}));

    REQUIRE(pkb_read_facade_->GetNextBy("6", READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"5"}));

    REQUIRE(pkb_read_facade_->HasNextBy("2") == true);

    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("1", "2"),
                                                          std::make_pair("2", "3"),
                                                          std::make_pair("3", "4"),
                                                          std::make_pair("5", "6"),
                                                          std::make_pair("2", "5")
                                                      }));

    REQUIRE(pkb_read_facade_->GetNextFirst(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "2", "3", "5"}));

    REQUIRE(pkb_read_facade_->GetNextSecond(READ) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "3", "4", "5", "6"}));
  }
}

TEST_CASE("Testing Parent API") {
  SECTION("Parent API") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;

    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddStatementOfAType("1", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("3", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("5", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("6", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("7", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("8", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("9", ASSIGN);

    pkb_write_facade_->AddParentRelation("1", "2");
    pkb_write_facade_->AddParentRelation("1", "3");
    pkb_write_facade_->AddParentRelation("2", "4");
    pkb_write_facade_->AddParentRelation("2", "5");
    pkb_write_facade_->AddParentRelation("2", "6");
    pkb_write_facade_->AddParentRelation("3", "7");
    pkb_write_facade_->AddParentRelation("3", "8");
    pkb_write_facade_->AddParentRelation("6", "9");
    pkb_write_facade_->AddParentRelation("7", "9");
    pkb_write_facade_->AddParentRelation("9", "10");
    pkb_write_facade_->AddParentRelation("9", "11");
    pkb_write_facade_->AddParentStarRelation();

    REQUIRE_FALSE(pkb_read_facade_->GetParentChildPairs(ASSIGN, ASSIGN) ==
            std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                               PairHasherUtil::hash_pair>({
                std::make_pair("1", "2"),
                std::make_pair("2", "3"),
                std::make_pair("3", "4"),
                std::make_pair("5", "6"),
                std::make_pair("2", "5")
            }));
    REQUIRE(pkb_read_facade_->GetStatementThatIsParentOf("2", ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
                ({"1"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreChildrenOf("1", ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"3", "2"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreParents(ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"9", "6", "7", "3", "2", "1"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreChildren(ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
        ({"9", "6", "7", "5", "8", "4", "3", "2"}));
    REQUIRE(pkb_read_facade_->HasParentChildRelationship("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsAnyParentRelationshipPresent() == true);
  }

  SECTION("Parent* API") {
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;

    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddStatementOfAType("1", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("3", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("5", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("6", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("7", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("8", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("9", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("10", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("11", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("12", ASSIGN);

    pkb_write_facade_->AddParentRelation("1", "2");
    pkb_write_facade_->AddParentRelation("1", "3");
    pkb_write_facade_->AddParentRelation("2", "4");
    pkb_write_facade_->AddParentRelation("3", "4");
    pkb_write_facade_->AddParentRelation("4", "5");
    pkb_write_facade_->AddParentRelation("4", "6");
    pkb_write_facade_->AddParentRelation("4", "7");
    pkb_write_facade_->AddParentRelation("4", "8");
    pkb_write_facade_->AddParentRelation("5", "10");
    pkb_write_facade_->AddParentRelation("6", "9");
    pkb_write_facade_->AddParentRelation("7", "9");
    pkb_write_facade_->AddParentRelation("8", "11");
    pkb_write_facade_->AddParentRelation("9", "10");
    pkb_write_facade_->AddParentRelation("9", "11");
    pkb_write_facade_->AddParentRelation("9", "12");
    pkb_write_facade_->AddParentStarRelation();

    REQUIRE_FALSE(pkb_read_facade_->GetAncestorDescendantPairs(ASSIGN, ASSIGN) ==
                  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                                     PairHasherUtil::hash_pair>({
                      std::make_pair("1", "2"),
                      std::make_pair("2", "3"),
                      std::make_pair("3", "4"),
                      std::make_pair("5", "6"),
                      std::make_pair("2", "5")
                  }));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreAncestorOf("2", ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"1"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreAncestors(ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"3", "2", "1", "9", "6", "5", "7", "8", "4"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatAreDescendants(ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"2", "3", "12", "10", "4", "8", "6", "11", "9", "7", "5"}));
    REQUIRE(pkb_read_facade_->IsAnyAncestorDescendantRelationshipPresent() == true);
    REQUIRE(pkb_read_facade_->HasAncestorDescendantRelationship("1", "2") == true);
    REQUIRE(pkb_read_facade_->GetStatementsThatAreDescendantsOf("2", ASSIGN)
            == std::unordered_set<PkbTypes::STATEMENT_NUMBER>
            ({"7", "5", "6", "9", "11", "12", "10", "8", "4"}));
  }
}

TEST_CASE("Testing Pattern API") {
  SECTION("Test Assign and Expression") {
    typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
    typedef std::vector<std::shared_ptr<Token>> TokenList;

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

    pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
    pkb_write_facade_->AddStatementModifyingVariable("2", "i");
    pkb_write_facade_->AddAssignmentStatementAndExpression(
        "2", egs->GetExpressionFromInput(
                 token_list_statement_2, "assign"));

    REQUIRE(pkb_read_facade_->GetAssignWithExactExpression(egs->GetExpressionFromInput(
        token_list_statement_2, "assign")) == std::unordered_set<std::string>({"2"}));

    REQUIRE(pkb_read_facade_->GetAssignWithPartialExpression(egs->GetExpressionFromInput(
                token_list_statement_2, "assign")) == std::unordered_set<std::string>({"2"}));

    REQUIRE(pkb_read_facade_->RetrieveAllVariablesOfExpression(egs->GetExpressionFromInput(
                token_list_statement_2, "assign")) == std::unordered_set<std::string>({}));

    REQUIRE(pkb_read_facade_->RetrieveAllVariablesOfExpression(egs->GetExpressionFromInput(
                token_list_statement_4, "assign")) == std::unordered_set<std::string>({}));
  }

  SECTION("Test expression within If statement") {
    typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
    typedef std::vector<std::shared_ptr<Token>> TokenList;

    // x > 0
    TokenList token_list_statement_10{
        make_shared<NameToken>("x"),
        make_shared<ArithmeticOperatorToken>(">", GT),
        make_shared<IntegerToken>("0"),
    };

    pkb_write_facade_->AddStatementOfAType("10", IF);
    pkb_write_facade_->AddStatementModifyingVariable("10", "z");
    pkb_write_facade_->AddAssignmentStatementAndExpression(
        "10", egs->GetExpressionFromInput(
                  token_list_statement_10, "if"));

    // y > 0
    TokenList token_list_statement_11{
        make_shared<NameToken>("y"),
        make_shared<ArithmeticOperatorToken>(">", GT),
        make_shared<IntegerToken>("0"),
    };

    pkb_write_facade_->AddStatementOfAType("11", WHILE);
    pkb_write_facade_->AddStatementModifyingVariable("11", "z");
    pkb_write_facade_->AddAssignmentStatementAndExpression(
        "11", egs->GetExpressionFromInput(
                  token_list_statement_11, "while"));

    REQUIRE(pkb_read_facade_->GetIfConditionVariablePair() ==
            std::unordered_set<std::pair<PkbTypes::VARIABLE, PkbTypes::STATEMENT_NUMBER>,
                PairHasherUtil::hash_pair>({}));
    REQUIRE(pkb_read_facade_->GetIfWithConditionVariable("x") == std::unordered_set<std::string>({}));
    REQUIRE(pkb_read_facade_->GetIfThatHasConditionVariable() == std::unordered_set<std::string>({}));
    REQUIRE(pkb_read_facade_->GetWhileConditionVariablePair() ==
            std::unordered_set<std::pair<PkbTypes::VARIABLE, PkbTypes::STATEMENT_NUMBER>,
                PairHasherUtil::hash_pair>({}));
    REQUIRE(pkb_read_facade_->GetWhileWithConditionVariable("y") == std::unordered_set<std::string>({}));
    REQUIRE(pkb_read_facade_->GetWhileThatHasConditionVariable() == std::unordered_set<std::string>({}));
  }
}

TEST_CASE("Testing Affects") {
  SECTION("Test Affects API - Complex CFG and Expressions") {
    typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;
    Pkb pkb_ = Pkb();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

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
    pkb_write_facade_->AddStatementUsingVariable("5", "v");

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

    REQUIRE(pkb_read_facade_->IsThereAnyAffectsRelationship() == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("2", "6") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("4", "8") == false);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("4", "10") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("6", "6") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("1", "4") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("1", "8") == false);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("1", "10") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("1", "12") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("2", "10") == true);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("9", "10") == true);
    REQUIRE(pkb_read_facade_->GetAssignsAffectedBy("2") == std::unordered_set<std::string>({"10", "4", "6"}));
    REQUIRE(pkb_read_facade_->GetAssignsAffecting("2") == std::unordered_set<std::string>({}));
    REQUIRE(pkb_read_facade_->GetAllAssignsThatAffect()
            == std::unordered_set<std::string>({"1", "2", "11", "6", "9", "4", "10", "8"}));
    REQUIRE(pkb_read_facade_->GetAllAssignsThatAreAffected()
            == std::unordered_set<std::string>({"6", "12", "11", "4", "10"}));
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("9", "11") == false);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("9", "12") == false);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("2", "3") == false);
    REQUIRE(pkb_read_facade_->HasAffectsRelationship("9", "6") == false);
    REQUIRE_FALSE(pkb_read_facade_->GetAffectsStarPairs() == std::unordered_set<
        std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({}));
    REQUIRE_FALSE(pkb_read_facade_->GetAssignsAffectedStarBy("2") == std::unordered_set<std::string>({}));
    REQUIRE(pkb_read_facade_->GetAssignsAffectingStar("3") == std::unordered_set<std::string>({}));
    REQUIRE_FALSE(pkb_read_facade_->GetAllAssignsThatAffectStar() == std::unordered_set<std::string>({"2"}));
    REQUIRE(pkb_read_facade_->GetAllAssignsThatAreAffectedStar()
            == std::unordered_set<std::string>({"6", "12", "11", "4", "10"}));
    REQUIRE(pkb_read_facade_->HasAffectsStarRelationship("2", "3")
            == false);
    REQUIRE(pkb_read_facade_->IsThereAnyAffectsStarRelationship());
  }
}


