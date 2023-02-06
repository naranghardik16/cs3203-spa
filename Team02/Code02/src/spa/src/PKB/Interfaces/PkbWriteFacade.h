#pragma once
#include "PKB/Types/PkbTypes.h"
#include "PKB/PKB.h"

/**
 * Facade implementation consisting of write methods
 * which acts as an interface between SP and PKB
 */
class PkbWriteFacade {
 private:
  PKB& pkb;

 public:
  PkbWriteFacade(PKB &pkb);

  ~PkbWriteFacade();

  /**
   * Adds variable into PKB
   *
   * @param variable - the target variable to add into PKB
   * @return index to store variable index
   */
  PkbTypes::INDEX AddVariable(PkbTypes::VARIABLE variable);

  /**
   *  Adds procedure into PKB
   *
   * @param procedure - the target procedure to add into PKB
   * @return index to store procedure index
   */
  PkbTypes::INDEX AddProcedure(PkbTypes::PROCEDURE procedure);

  /**
   * Adds constant into PKB
   *
   * @param constant - the target constant to add into PKB
   * @return index to store constant index
   */
  PkbTypes::INDEX AddConstant(PkbTypes::CONSTANT constant);
};