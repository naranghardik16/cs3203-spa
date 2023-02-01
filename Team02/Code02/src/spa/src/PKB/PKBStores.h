#pragma once

#include <string>
#include <unordered_set>
#include "General/KeyValueStore.h"
#include "TNode.h"

class PKBStores {
 public:
  typedef std::string PROCEDURE;
  typedef std::string VARIABLE;
  typedef std::string LINE_NUMBER;
  typedef std::string CONSTANT;
  typedef uint64_t VARIABLE_STORE_INDEX;
  typedef uint64_t PROCEDURE_STORE_INDEX;

  typedef KeyValueStore<VARIABLE, VARIABLE_STORE_INDEX> VARIABLE_STORE;
  typedef KeyValueStore<PROCEDURE, PROCEDURE_STORE_INDEX> PROCEDURE_STORE;
  typedef std::unordered_set<CONSTANT> CONSTANT_STORE;


  virtual const VARIABLE_STORE &getVariableStore() const = 0;

  virtual const PROCEDURE_STORE &getProcedureStore() const = 0;

  virtual const CONSTANT_STORE &getConstantStore() const = 0;

  virtual void addConstant(CONSTANT constant) = 0;

  virtual VARIABLE_STORE_INDEX addVariable(VARIABLE variable) = 0;

  virtual PROCEDURE_STORE_INDEX addProcedure(PROCEDURE procedure) = 0;

 protected:
  VARIABLE_STORE variable_store_;
  PROCEDURE_STORE procedure_store_;
  CONSTANT_STORE constant_store_;

};

