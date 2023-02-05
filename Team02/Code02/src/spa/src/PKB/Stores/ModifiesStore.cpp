
#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

KeyValueStore<PkbTypes::LINE_NUMBER, PkbTypes::MODIFIES> &ModifiesStore::getModifiesStatementStore() {
  return this->modifies_statement_store_;
}

void ModifiesStore::addModifiesStatement(PkbTypes::LINE_NUMBER line_number, PkbTypes::MODIFIES modifies) {
  this->modifies_statement_store_.insert({line_number, modifies});
}

void ModifiesStore::addModifiesProcedure(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE_SET variable_set) {
  this->modifies_procedure_store_.insert({procedure, variable_set});
}

KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE_SET> &ModifiesStore::getModifiesProcedureStore() {
  return this->modifies_procedure_store_;
}
