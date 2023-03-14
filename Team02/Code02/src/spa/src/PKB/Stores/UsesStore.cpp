#include "UsesStore.h"

UsesStore::UsesStore() {}

UsesStore::~UsesStore() {}

void UsesStore::addStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) {
  this->uses_statement_variable_.insert(statement_number, variable);
}

void UsesStore::addProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->uses_procedure_variable_.insert(procedure, variable);
}

std::unordered_set<PkbTypes::VARIABLE>
    UsesStore::retrieveAllVariablesUsedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->uses_statement_variable_.retrieveFromKey(statement_number);
}

std::unordered_set<PkbTypes::VARIABLE> UsesStore::retrieveAllVariablesUsedByAProcedure(PkbTypes::PROCEDURE procedure) {
  return this->uses_procedure_variable_.retrieveFromKey(procedure);
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
    UsesStore::retrieveStatementVariablePairs() {
  return this->uses_statement_variable_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
    UsesStore::retrieveProcedureVariablePairs() {
  return this->uses_procedure_variable_.retrieveAll();
}

bool UsesStore::hasUsesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                           PkbTypes::VARIABLE variable) {
  return this->uses_statement_variable_.contains(statement_number, variable);
}

bool UsesStore::hasUsesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  return this->uses_procedure_variable_.contains(procedure, variable);
}

std::unordered_set<PkbTypes::PROCEDURE> UsesStore::retrieveAllProceduresThatUse() {
  return this->uses_procedure_variable_.retrieveAllKeys();
}









