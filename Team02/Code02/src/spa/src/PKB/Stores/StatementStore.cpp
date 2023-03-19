#include "StatementStore.h"

StatementStore::StatementStore() = default;

StatementStore::~StatementStore() = default;

void StatementStore::AddStatementAndField(const StatementNumber& statement_number, const Field& field) {
  this->statement_field_store_.insert(statement_number, field);
}

void StatementStore::AddStatementAndType(const StatementType& statement_type,
                                         const StatementNumber& statement_number) {
  this->type_statement_store_.insert(statement_type, statement_number);
}

StatementType StatementStore::GetType(const StatementNumber& statement_number) {
  return this->type_statement_store_.retrieveFromValue(statement_number);
}

StatementStore::StatementNumberSet StatementStore::GetStatements(const StatementType& statement_type) {
  if (statement_type == STATEMENT) return this->GetStatements();
  return this->type_statement_store_.retrieveFromKey(statement_type);
}

StatementStore::StatementTypeSet StatementStore::GetTypes() {
  return this->type_statement_store_.retrieveAllKeys();
}

StatementStore::StatementNumberSet StatementStore::GetStatements() {
  return this->type_statement_store_.retrieveAllValues();
}

StatementStore::FieldSet StatementStore::GetFields(const StatementNumber& statement_number) {
  return this->statement_field_store_.retrieveFromKey(statement_number);
}

