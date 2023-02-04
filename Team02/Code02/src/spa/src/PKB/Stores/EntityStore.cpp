#include "EntityStore.h"

KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX>  &EntityStore::getVariableStore() {
  return this->variable_store_;
}

KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &EntityStore::getProcedureStore() {
  return this->procedure_store_;
}

std::unordered_set<PkbTypes::CONSTANT> &EntityStore::getConstantStore() {
  return this->constant_store_;
}

PkbTypes::VARIABLE_STORE_INDEX EntityStore::addVariable(PkbTypes::VARIABLE variable) {
  PkbTypes::VARIABLE_STORE_INDEX index = this->variable_store_.size() + 1;
  if (this->variable_store_.insert({variable, index})) {
    return index;
  } else {
    return this->variable_store_.map[variable];
  }
}

PkbTypes::PROCEDURE_STORE_INDEX EntityStore::addProcedure(PkbTypes::PROCEDURE procedure) {
  PkbTypes::PROCEDURE_STORE_INDEX index = this->procedure_store_.size() + 1;
  if (this->procedure_store_.insert({procedure, index})) {
    return index;
  } else {
    return this->procedure_store_.map[procedure];
  }
}

void EntityStore::addConstant(PkbTypes::CONSTANT constant) {
  this->constant_store_.insert(constant);
}
