
#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

ModifiesStore::~ModifiesStore() {}

void ModifiesStore::addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) {
  this->modifies_statement_variable_.insert(statement_number, variable);
}

void ModifiesStore::addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->modifies_procedure_variable_.insert(procedure, variable);
}

std::vector<std::vector<std::string>> ModifiesStore::convert(std::vector<std::string> s) {
  std::vector<std::vector<std::string>> result;
  for (auto value: s) {
    result.push_back(std::vector<std::string> {value});
  }
  return result;
}

std::vector<PkbTypes::VARIABLE> ModifiesStore::retrieveAllVariablesModifiedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->modifies_statement_variable_.retrieveFromKey(statement_number);
}

std::vector<std::vector<std::string>> ModifiesStore::pipe(std::vector<std::string> input) {
  return this->pipe(input);
}


