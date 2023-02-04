#pragma once
#include "PKB/Types/PkbTypes.h"
#include "PKB/PKB.h"

class PkbWriteFacade {
 private:
  PKB& pkb;

 public:
  PkbWriteFacade(PKB &pkb);

  ~PkbWriteFacade();

  void AddConstant(PkbTypes::CONSTANT constant);

  PkbTypes::VARIABLE_STORE_INDEX AddVariable(PkbTypes::VARIABLE variable);

  PkbTypes::PROCEDURE_STORE_INDEX AddProcedure(PkbTypes::PROCEDURE procedure);
};