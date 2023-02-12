#pragma once

#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"

/**
 * Facade implementation consisting of write methods
 * which acts as an interface between SP and PKB
 */
class PkbWriteFacade {
 private:
  PKB& pkb;

 public:
  explicit PkbWriteFacade(PKB &pkb);

  ~PkbWriteFacade();

  /**
   * Adds variable into PKB
   *
   * @param variable - the target variable to add into PKB
   * @return index to store variable index
   */
  PkbTypes::INDEX AddVariable(PkbTypes::VARIABLE variable) const;

  /**
   *  Adds procedure into PKB
   *
   * @param procedure - the target procedure to add into PKB
   * @return index to store procedure index
   */
  PkbTypes::INDEX AddProcedure(PkbTypes::PROCEDURE procedure) const;

  /**
   * Adds constant into PKB
   *
   * @param constant - the target constant to add into PKB
   * @return index to store constant index
   */
  PkbTypes::INDEX AddConstant(PkbTypes::CONSTANT constant) const;

  void AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) const;

  void AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const;

  void AddFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1, PkbTypes::STATEMENT_NUMBER statement_number_2) const;
};