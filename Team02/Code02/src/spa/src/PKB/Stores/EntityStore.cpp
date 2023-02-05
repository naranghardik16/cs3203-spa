#include "EntityStore.h"

PkbTypes::INDEX EntityStore::addVariable(PkbTypes::VARIABLE variable) {
  PkbTypes::INDEX index = this->variable_store_.length() + 1;
  this->variable_store_.insert(std::move(variable), index);
  return index;
}

PkbTypes::INDEX EntityStore::addProcedure(PkbTypes::PROCEDURE procedure) {
  PkbTypes::INDEX index = this->procedure_store_.length() + 1;
  this->procedure_store_.insert(std::move(procedure), index);
  return index;
}

PkbTypes::INDEX EntityStore::addConstant(PkbTypes::CONSTANT constant) {
  PkbTypes::INDEX index = this->constant_store_.length() + 1;
  this->constant_store_.insert(std::move(constant), index);
  return index;
}

std::unordered_set<PkbTypes::VARIABLE> EntityStore::getVariables() {
  return this->variable_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::VARIABLE> EntityStore::getProcedures() {
  return this->procedure_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::CONSTANT> EntityStore::getConstants() {
  return this->constant_store_.retrieveAllKeys();
}

