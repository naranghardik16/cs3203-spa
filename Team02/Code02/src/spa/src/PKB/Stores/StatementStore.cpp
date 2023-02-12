#include "StatementStore.h"

StatementStore::StatementStore() = default;

StatementStore::~StatementStore() = default;

void StatementStore::addStatementAndField(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::FIELD field) {
  this->statement_field_store.insert(statement_number, field);
}

void StatementStore::addStatementForAType(StatementType statement_type, PkbTypes::STATEMENT_NUMBER statement_number) {
  this->type_statement_store.insert(statement_type, statement_number);
}

StatementType StatementStore::getStatementTypeByNumber(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->type_statement_store.retrieveFromValue(statement_number);
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> StatementStore::getStatementsFromType(StatementType statement_type) {
  return this->type_statement_store.retrieveFromKey(statement_type);
}

std::unordered_set<StatementType> StatementStore::getAllStatementTypes() {
  return this->type_statement_store.retrieveAllKeys();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> StatementStore::getAllStatements() {
  return this->type_statement_store.retrieveAllValues();
}

std::unordered_set<PkbTypes::FIELD> StatementStore::getFieldsForStatement(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->statement_field_store.retrieveFromKey(statement_number);
}


