#include "PkbReadFacade.h"
#include <memory>
#include "PKB/PKB.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

SingleConstraintSet PkbReadFacade::GetVariables() {
  return this->pkb.entity_store_->getVariables();
}

SingleConstraintSet PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->getConstants();
}

SingleConstraintSet PkbReadFacade::GetProcedures() {
  return this->pkb.entity_store_->getProcedures();
}

SingleConstraintSet PkbReadFacade::GetStatements() {
  return this->pkb.statement_store_->getAllStatements();
}

SingleConstraintSet PkbReadFacade::GetReadStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::READ);
}

SingleConstraintSet PkbReadFacade::GetPrintStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::PRINT);
}

SingleConstraintSet PkbReadFacade::GetCallStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::CALL);
}

SingleConstraintSet PkbReadFacade::GetWhileStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::WHILE);
}

SingleConstraintSet PkbReadFacade::GetIfStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::IF);
}

SingleConstraintSet PkbReadFacade::GetAssignStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::ASSIGN);
}


//! Modifies Statement API
PairConstraintSet PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  PairConstraintSet result;
  return result;
}

//TODO to put back the proper PKB implementation after type of return value is change to set
SingleConstraintSet PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  //return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet PkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
  SingleConstraintSet result;
  return result;
}

bool PkbReadFacade::HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  return true;
}


//! Modifies Procedure API
PairConstraintSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  PairConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure_name) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet PkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetProceduresThatModify() {
  SingleConstraintSet result;
  return result;
}

bool PkbReadFacade::HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  return true;
}

//! Follows API
PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  PairConstraintSet result;
  return result;
}


SingleConstraintSet PkbReadFacade::GetStatementsFollowedBy(std::string statement_num, StatementType statement_type) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetStatementsFollowing(std::string statement_num, StatementType statement_type) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet PkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  SingleConstraintSet result;
  return result;
}


bool PkbReadFacade::HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  return true;
}

bool PkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return true;
}

