#include "PKB.h"

const PKBStores::VARIABLE_STORE &PKB::getVariableStore() const {
  return this->variable_store_;
}

const PKBStores::PROCEDURE_STORE &PKB::getProcedureStore() const {
  return this->procedure_store_;
}

const PKBStores::CONSTANT_STORE &PKB::getConstantStore() const {
  return this->constant_store_;
}

PKBStores::VARIABLE_STORE_INDEX PKB::addVariable(PKBStores::VARIABLE variable) {
  VARIABLE_STORE_INDEX index = this->variable_store_.size() + 1;
  if (this->variable_store_.insert({variable, index})) {
    return index;
  } else {
    return this->variable_store_.map[variable];
  }
}

PKBStores::PROCEDURE_STORE_INDEX PKB::addProcedure(PKBStores::PROCEDURE procedure) {
  PROCEDURE_STORE_INDEX index = this->procedure_store_.size() + 1; // offset index by 1
  if (this->procedure_store_.insert({procedure, index})) {
    return index; // if insertion took place, return insertion index
  } else {
    return this->procedure_store_.map[procedure]; // otherwise, return existing index
  }
}

void PKB::addConstant(PKBStores::CONSTANT constant) {
  this->constant_store_.insert(constant);
}

PKBStores *PKB::getStores() {
  return this;
}
