
#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

ModifiesStore::~ModifiesStore() {}

void ModifiesStore::addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) {
  this->modifies_statement_variable_.insert(statement_number, variable);
}

void ModifiesStore::addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->modifies_procedure_variable_.insert(procedure, variable);
}
//
//std::vector<std::vector<std::string>> ModifiesStore::convert(std::vector<std::string> s) {
//  std::vector<std::vector<std::string>> result;
//  for (auto value: s) {
//    std::vector<std::string> v = {value};
//    result.push_back(v);
//  }
//  return result;
//}

std::unordered_set<PkbTypes::VARIABLE> ModifiesStore::retrieveAllVariablesModifiedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->modifies_statement_variable_.retrieveFromKey(statement_number);
}

