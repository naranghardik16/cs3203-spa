#pragma once
#include "PKB/Types/PkbTypes.h"
#include "PKB/PKB.h"

class PkbWriteFacade {
 private:
  PKB& pkb;

 public:
  PkbWriteFacade(PKB &pkb);

  ~PkbWriteFacade();

  PkbTypes::INDEX AddVariable(PkbTypes::VARIABLE variable);

  PkbTypes::INDEX AddProcedure(PkbTypes::PROCEDURE procedure);

  PkbTypes::INDEX AddConstant(PkbTypes::CONSTANT constant);

  void AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);

  void AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);
};