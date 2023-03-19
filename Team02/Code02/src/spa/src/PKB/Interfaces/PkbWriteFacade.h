#pragma once

#include "General/StatementTypeEnum.h"
#include "PKB/Pkb.h"
#include "PKB/Types/PkbTypes.h"
#include "core/cfg_model/Cfg.h"

/**
 * Facade implementation consisting of write methods
 * which acts as an interface between SP and Pkb
 */
class PkbWriteFacade {
 private:
  Pkb &pkb;

 public:
  explicit PkbWriteFacade(Pkb &pkb);

  ~PkbWriteFacade();

  /**
   * Adds variable into Pkb
   *
   * @param variable - the target variable to add into Pkb
   * @return index to store variable index
   */
  PkbTypes::INDEX AddVariable(PkbTypes::VARIABLE variable) const;

  /**
   *  Adds procedure into Pkb
   *
   * @param procedure - the target procedure to add into Pkb
   * @return index to store procedure index
   */
  PkbTypes::INDEX AddProcedure(PkbTypes::PROCEDURE procedure) const;

  /**
   * Adds constant into Pkb
   *
   * @param constant - the target constant to add into Pkb
   * @return index to store constant index
   */
  PkbTypes::INDEX AddConstant(PkbTypes::CONSTANT constant) const;

  /**
   * Adds a statement number and the corresponding variable being used into the Pkb.
   *
   * @param statement_number - The statement number to be added to the Pkb.
   * @param variable - The variable that is being used by the statement with the given statement number.
   */
  void AddStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                 PkbTypes::VARIABLE variable) const;

  /**
   * Adds a statement number and the corresponding type of the statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of the statement.
   */
  void AddStatementOfAType(PkbTypes::STATEMENT_NUMBER statement_number,
                           StatementType statement_type) const;

  /**
   * Adds a procedure and the corresponding variable being used into the Pkb.
   *
   * @param procedure - The procedure to be added to the Pkb.
   * @param variable - The variable that is being used within the given procedure.
   */
  void AddProcedureUsingVariable(PkbTypes::PROCEDURE procedure,
                                 PkbTypes::VARIABLE variable) const;

  /**
   * Adds a statement number and its corresponding modifying variable into Pkb.
   *
   * @param statement_number - The statement number to be added to the Pkb.
   * @param variable - The variable that is being modified by the statement with the given statement number.
   */
  void AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                     PkbTypes::VARIABLE variable) const;

  /**
   * Adds a procedure and its corresponding modifying variable into Pkb.
   *
   * @param procedure - The procedure to be added to the Pkb.
   * @param variable - The variable that is being modified within the given procedure.
   */
  void AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure,
                                     PkbTypes::VARIABLE variable) const;

  /**
   * Adds a follows relationship between two statements into the Pkb.
   *
   * @param statement_number_1 - The statement number of the first statement in the follows relationship.
   * @param statement_number_2 - The statement number of the second statement in the follows relationship.
   */
  void AddFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                          PkbTypes::STATEMENT_NUMBER statement_number_2) const;

  /**
   * Adds a parent relationship between two statements into the Pkb.
   *
   * @param statement_number_1 - The statement number of the first statement in the parent relationship.
   * @param statement_number_2 - The statement number of the second statement in the parent relationship.
   */
  void AddParentRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                         PkbTypes::STATEMENT_NUMBER statement_number_2) const;

  /**
   * Adds an assignment statement and its expression into the Pkb.
   *
   * @param statement_number - The statement number of the assignment statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddAssignmentStatementAndExpression(PkbTypes::STATEMENT_NUMBER statement_number,
                                           std::shared_ptr<Expression> expression);

  /**
   * Adds an if statement and its condition into the Pkb.
   *
   * @param statement_number - The statement number of the if statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                  std::shared_ptr<Expression> expression);

  /**
   * Adds a while statement and its condition into the Pkb.
   *
   * @param statement_number - The statement number of the while statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                     std::shared_ptr<Expression> expression);

   /**
    * Adds calls relation to the Pkb.
    *
    * @param caller_procedure - The caller procedure.
    * @param callee_procedure - The callee procedure.
    */
   void AddCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  void AddCallsStarRelation();
   /**
    * Adds calls statement to procedure name mapping to Pkb.
    *
    * @param statement_number - The statement number associated with the call statement.
    * @param procedure - The procedure being called as a part of that statement.
    */
   void AddCallStatementToProcedureName(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::PROCEDURE procedure);

   /**
    * Adds control flow graph to Pkb.
    *
    * @param cfg - The control flow graph to be added.
    */
   void AddCfg(std::shared_ptr<Cfg>& cfg);
};

