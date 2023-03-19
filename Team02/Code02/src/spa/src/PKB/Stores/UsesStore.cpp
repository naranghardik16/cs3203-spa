#include "UsesStore.h"

UsesStore::UsesStore() {}

UsesStore::~UsesStore() {}

void UsesStore::AddStatementUsesVariable(const StatementNumber& statement_number, const Variable& variable) {
  this->uses_statement_variable_store_.insert(statement_number, variable);
}

void UsesStore::AddProcedureUsesVariable(const Procedure& procedure, const Variable& variable) {
  this->uses_procedure_variable_store_.insert(procedure, variable);
}

UsesStore::VariableSet UsesStore::retrieveAllVariablesUsedByAStatement(const StatementNumber& statement_number) {
  return this->uses_statement_variable_store_.retrieveFromKey(statement_number);
}

UsesStore::VariableSet UsesStore::GetVariablesUsedByProcedure(const Procedure& procedure) {
  return this->uses_procedure_variable_store_.retrieveFromKey(procedure);
}

UsesStore::StatementVariablePairSet UsesStore::GetStatementVariablePairs() {
  return this->uses_statement_variable_store_.retrieveAll();
}

UsesStore::ProcedureVariablePairSet UsesStore::GetProcedureVariablePairs() {
  return this->uses_procedure_variable_store_.retrieveAll();
}

bool UsesStore::HasUsesStatementVariableRelation(const StatementNumber& statement_number, const Variable& variable) {
  return this->uses_statement_variable_store_.contains(statement_number, variable);
}

bool UsesStore::HasUsesProcedureVariableRelation(const Procedure& procedure, const Variable& variable) {
  return this->uses_procedure_variable_store_.contains(procedure, variable);
}

UsesStore::ProcedureSet UsesStore::retrieveAllProceduresThatUse() {
  return this->uses_procedure_variable_store_.retrieveAllKeys();
}









