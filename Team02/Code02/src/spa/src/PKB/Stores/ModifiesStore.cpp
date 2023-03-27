#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

ModifiesStore::~ModifiesStore() {}

void ModifiesStore::AddStatementModifiesVariable(const StatementNumber &statement_number, const Variable &variable) {
  this->modifies_statement_variable_store_.insert(statement_number, variable);
}

void ModifiesStore::AddProcedureModifiesVariable(const Procedure &procedure, const Variable &variable) {
  this->modifies_procedure_variable_.insert(procedure, variable);
}

ModifiesStore::VariableSet
ModifiesStore::GetVariablesModifiedByStatement(const StatementNumber &statement_number) {
  return this->modifies_statement_variable_store_.retrieveFromKey(statement_number);
}

ModifiesStore::VariableSet
ModifiesStore::GetVariablesModifiedByProcedure(const Procedure &procedure) {
  return this->modifies_procedure_variable_.retrieveFromKey(procedure);
}

ModifiesStore::StatementVariablePairSet ModifiesStore::GetStatementVariablePairs() {
  return this->modifies_statement_variable_store_.retrieveAll();
}

ModifiesStore::ProcedureVariablePairSet ModifiesStore::GetProcedureVariablePairs() {
  return this->modifies_procedure_variable_.retrieveAll();
}

bool ModifiesStore::HasModifiesStatementVariableRelation(const StatementNumber &statement_number,
                                                         const Variable &variable) {
  return this->modifies_statement_variable_store_.contains(statement_number, variable);
}

bool ModifiesStore::HasModifiesProcedureVariableRelation(const Procedure &procedure,
                                                         const Variable &variable) {
  return this->modifies_procedure_variable_.contains(procedure, variable);
}

ModifiesStore::ProcedureSet ModifiesStore::GetProceduresThatModify() {
  return this->modifies_procedure_variable_.retrieveAllKeys();
}

