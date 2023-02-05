#include "StatmentStore.h"

StatementStore::StatementStore() {}

KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::PROCEDURE> &StatementStore::getStatementProcedureStore() {
  return this->statement_procedure_store_;
}

KeyValueStore<PkbTypes::LINE_NUMBER, StatementType> &StatementStore::getStatementTypeStore() {
  return this->statement_type_store_;
}

void StatementStore::addStatementProcedure(PkbTypes::LINE_NUMBER line_number, PkbTypes::PROCEDURE statement_procedure) {
  this->statement_procedure_store_.insert({line_number, statement_procedure});
}

void StatementStore::addStatementType(PkbTypes::LINE_NUMBER line_number, StatementType statement_type) {
  this->statement_type_store_.insert({line_number, statement_type});
}

