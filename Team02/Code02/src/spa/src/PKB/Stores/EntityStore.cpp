#include "EntityStore.h"

#include <iostream>

//EntityStore::~EntityStore() {}

PkbTypes::INDEX EntityStore::addVariable(PkbTypes::VARIABLE variable) {
  PkbTypes::INDEX index = variable_store_.length() + 1;
  variable_store_.insert(variable, index);
  return 1;
}

PkbTypes::INDEX EntityStore::addProcedure(PkbTypes::PROCEDURE procedure) {
  PkbTypes::INDEX index = procedure_store_.length() + 1;
  procedure_store_.insert(procedure, index);
  return 1;
}

PkbTypes::INDEX EntityStore::addConstant(PkbTypes::CONSTANT constant) {
  PkbTypes::INDEX index = constant_store_.length() + 1;
  constant_store_.insert(constant, index);
  return 1;
}

std::unordered_set<PkbTypes::VARIABLE> EntityStore::getVariables() {
  return variable_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::PROCEDURE> EntityStore::getProcedures() {
  return procedure_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::CONSTANT> EntityStore::getConstants() {
  return constant_store_.retrieveAllKeys();
}

