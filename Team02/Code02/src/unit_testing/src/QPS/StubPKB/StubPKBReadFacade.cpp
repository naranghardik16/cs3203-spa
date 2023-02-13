//! Preserving the stub written previously

#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::StubPkbReadFacade(PKB &pkb): PkbReadFacade(pkb) {}

StubPkbReadFacade::~StubPkbReadFacade() {}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariables() {
  PkbCommunicationTypes::SingleConstraintSet var_set({"a", "x", "y"});
  return var_set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetConstants() {
  PkbCommunicationTypes::SingleConstraintSet set({"22", "23", "24"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProcedures() {
  PkbCommunicationTypes::SingleConstraintSet set({"execute", "anya"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatements() {
  return {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetReadStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"1"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetPrintStatements() {
  PkbCommunicationTypes::SingleConstraintSet print_set({"4","9"});
  return print_set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetCallStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"3"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetWhileStatements() {
  return {"8"};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetIfStatements() {
  return {"5"};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetAssignStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"2", "6", "7"});
  return set;
}


//! Modifies Statement API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::READ) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {std::make_pair("2", "a")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  if (statement_number == "1") {
    return {"x"};
  }
  if (statement_number == "2") {
    return {"a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"x\"" && statement_type == StatementType::READ) {
    return {"1"};
  }
  if (var_name == "\"a\"" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
  if (stmt_type == StatementType::READ) {
    return {"1"};
  }
  if (stmt_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

bool StubPkbReadFacade::HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  if (stmt_num == "1" && var_name == "\"x\"") {
    return true;
  }
  if (stmt_num == "2" && var_name == "\"a\"") {
    return true;
  }
  return false;
}


//! Modifies Procedure API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "x"), std::make_pair("execute", "a")};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure_name) {
  if (procedure_name == "\"execute\"") {
    return {"x","a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  if (var_name == "\"x\"") {
    return {"execute"};
  }
  if (var_name == "\"a\"") {
    return {"execute"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresThatModify() {
  return {"execute"};
}

bool StubPkbReadFacade::HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  if (procedure_name == "\"execute\"" && var_name == "\"x\"") {
    return true;
  }
  if (procedure_name == "\"execute\"" && var_name == "\"a\"") {
    return true;
  }
  return false;
}

//! Uses Statement API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetUsesStatementVariablePairs(StatementType statement_type) {
  return {{"2", "x"}, {"2", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatUses(StatementType statement_type) {
  return {"2"};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesUsedByStatement(std::string statement_number) {
  if (statement_number == "2") {
    return {"x", "y"};
  } else {
    return {};
  }
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsUsesVariable(StatementType statement_type, std::string variable) {
  return {"2"};
}

bool StubPkbReadFacade::HasUsesStatementRelationship(std::string statement_number, std::string variable) {
  if (statement_number == "2") {
    return true;
  } else {
    return false;
  }
}

//! Uses Procedure API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetUsesProcedureVariablePairs() {
  return {{"anya", "x"}, {"anya", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresThatUse() {
  return {"anya"};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesUsedByProcedure(std::string procedure) {
  if (procedure == "anya" ){
    return {"x", "y"};
  } else {
    return {};
  }
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresUsesVariable(std::string variable) {
  return {"anya"};
}

bool StubPkbReadFacade::HasUsesProcedureRelationship(std::string procedure, std::string variable) {
  if (procedure == "anya") {
    return true;
  } else {
    return false;
  }
}

//! Follows API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementFollowedBy(std::string statement_num, StatementType statement_type) {
  if (statement_num == "3" && statement_type == StatementType::STATEMENT) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementFollowing(std::string statement_num, StatementType statement_type) {
  if (statement_num == "1" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::ASSIGN)) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  if (statement_type == StatementType::READ) {
    return {"3"};
  }
  return {};
}


bool StubPkbReadFacade::HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  if (statement_num == "1" && statement_num_follower == "2") {
    return true;
  }
  if (statement_num == "1" && statement_num_follower == "3") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return true;
}

//! Parent API

PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetParentChildPairs(StatementType statement_type, StatementType statement_type_child) {
  if (statement_type == StatementType::IF && statement_type_child == StatementType::ASSIGN) {
    return {std::make_pair("5","6"), std::make_pair("5","7")};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type) {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "5" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::ASSIGN)) {
    return {"6","7"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreParents(StatementType statement_type) {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreChildren(StatementType statement_type) {
  if (statement_type == StatementType::ASSIGN) {
    return {"6","7"};
  }
  return {};
}

bool StubPkbReadFacade::HasParentChildRelationship(std::string statement_num, std::string statement_num_child) {
  if (statement_num == "5" && statement_num_child == "6") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyParentRelationshipPresent() {
  return true;
}

PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) {
  if (statement_type == StatementType::IF && statement_type_descendant == StatementType::PRINT) {
    return {std::make_pair("5","9")};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "9" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::IF)) {
    return {"5"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "5" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::PRINT)) {
    return {"9"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreAncestors(StatementType statement_type) {
  if (statement_type == StatementType::IF) {
    return {"5"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatAreDescendants(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {"9"};
  }
  return {};
}

bool StubPkbReadFacade::HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant) {
  if (statement_num == "5" && statement_num_descendant == "9") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return true;
}
