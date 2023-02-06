
#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

ModifiesStore::~ModifiesStore() {}

void ModifiesStore::addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) {
  this->modifies_statement_variable_.insert(statement_number, variable);
}

void ModifiesStore::addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->modifies_procedure_variable_.insert(procedure, variable);
}

