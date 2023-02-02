#pragma once
#include "PKB/Types/PkbTypes.h"
#include "PKB/PKB.h"

class PkbWriteFacade {
 private:
  PKB& pkb;

 public:
  PkbWriteFacade(PKB &pkb);

  ~PkbWriteFacade();

  void addConstant(PkbTypes::CONSTANT constant);

  PkbTypes::VARIABLE_STORE_INDEX addVariable(PkbTypes::VARIABLE variable);

  PkbTypes::PROCEDURE_STORE_INDEX addProcedure(PkbTypes::PROCEDURE procedure);
};