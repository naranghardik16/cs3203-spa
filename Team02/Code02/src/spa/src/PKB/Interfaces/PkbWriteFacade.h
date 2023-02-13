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

  /**
   * Adds a statement number and the corresponding variable being used into the PKB.
   *
   * @param statement_number - The statement number to be added to the PKB.
   * @param variable - The variable that is being used by the statement with the given statement number.
   */
  void AddStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) const;

  /**
   * Adds a procedure and the corresponding variable being used into the PKB.
   *
   * @param procedure - The procedure to be added to the PKB.
   * @param variable - The variable that is being used within the given procedure.
   */
  void AddProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const;

  /**
   * Adds a statement number and its corresponding modifying variable into PKB.
   *
   * @param statement_number - The statement number to be added to the PKB.
   * @param variable - The variable that is being modified by the statement with the given statement number.
   */
  void AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable) const;

  /**
   * Adds a procedure and its corresponding modifying variable into PKB.
   *
   * @param procedure - The procedure to be added to the PKB.
   * @param variable - The variable that is being modified within the given procedure.
   */
  void AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const;

  /**
   * Adds a follows relationship between two statements into the PKB.
   *
   * @param statement_number_1 - The statement number of the first statement in the follows relationship.
   * @param statement_number_2 - The statement number of the second statement in the follows relationship.
   */
  void AddFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1, PkbTypes::STATEMENT_NUMBER statement_number_2) const;
};