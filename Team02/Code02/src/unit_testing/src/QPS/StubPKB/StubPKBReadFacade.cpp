//! Preserving the stub written previously

#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::~StubPkbReadFacade() {}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariables() {
  PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet var_set({"a", "x", "y"});
  return var_set;
}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetConstants() {
  PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet set({"execute", "anya"});
  return set;
}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProcedures() {
  PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet set({"execute", "anya"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatements() {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetReadStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"4"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetPrintStatements() {
  PkbCommunicationTypes::SingleConstraintSet print_set({"1"});
  return print_set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetCallStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"3"});
  return set;
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetWhileStatements() {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetIfStatements() {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetAssignStatements() {
  PkbCommunicationTypes::SingleConstraintSet set({"2"});
  return set;
}


//! Modifies Statement API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {std::make_pair("2", "a")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  //return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
  if (statement_number == "1") {
    return {"x"};
  }
  if (statement_number == "2") {
    return {"a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"x\"" && statement_type == StatementType::PRINT) {
    return {"1"};
  }
  if (var_name == "\"a\"" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
  if (stmt_type == StatementType::PRINT) {
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

//! Follows API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  if (statement_type == StatementType::PRINT && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::PRINT && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsFollowedBy(std::string statement_num, StatementType statement_type) {
  if (statement_num == "3" && statement_type == StatementType::ALL) {
    return {"1","2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsFollowing(std::string statement_num, StatementType statement_type) {
  if (statement_num == "1" && statement_type == StatementType::ALL) {
    return {"2","3"};
  }
  if (statement_num == "1" && statement_type == StatementType::ASSIGN) {
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

