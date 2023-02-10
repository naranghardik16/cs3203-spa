
#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

ModifiesStore::~ModifiesStore() {}

void ModifiesStore::addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) {
  this->modifies_statement_variable_.insert(statement_number, variable);
}

void ModifiesStore::addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->modifies_procedure_variable_.insert(procedure, variable);
}

std::unordered_set<PkbTypes::VARIABLE> ModifiesStore::retrieveAllVariablesModifiedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->modifies_statement_variable_.retrieveFromKey(statement_number);
}

std::unordered_set<PkbTypes::VARIABLE> ModifiesStore::retrieveAllVariablesModifiedByAProcedure(PkbTypes::PROCEDURE procedure) {
  return this->modifies_procedure_variable_.retrieveFromKey(procedure);
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
    ModifiesStore::retrieveStatementVariablePairs() {
  return this->modifies_statement_variable_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
    ModifiesStore::retrieveProcedureVariablePairs() {
  return this->modifies_procedure_variable_.retrieveAll();
}

bool ModifiesStore::hasModifiesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                                   PkbTypes::VARIABLE variable) {
  return this->modifies_statement_variable_.contains(statement_number, variable);
}

bool ModifiesStore::hasModifiesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure,
PkbTypes::VARIABLE variable) {
  return this->modifies_procedure_variable_.contains(procedure, variable);
}

std::unordered_set<PkbTypes::PROCEDURE> ModifiesStore::retireveAllProceduresThatModify() {
  return this->modifies_procedure_variable_.retrieveAllKeys();
}

//std::vector<std::vector<std::string>> ModifiesStore::convert(std::vector<std::string> s) {
//  std::vector<std::vector<std::string>> result;
//  for (auto value: s) {
//    std::vector<std::string> v = {value};
//    result.push_back(v);
//  }
//  return result;
//}



