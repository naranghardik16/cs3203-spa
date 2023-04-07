#pragma once

#include <algorithm>
#include <unordered_set>

#include "core/cfg_model/Cfg.h"
#include "General/StatementTypeEnum.h"
#include "PKB/Pkb.h"
#include "PKB/Types/PkbTypes.h"

/**
 * Facade implementation consisting of write methods
 * which acts as an interface between Sp and Pkb.
 */
class PkbWriteFacade {
 private:
  Pkb &pkb;

 public:
  typedef PkbTypes::CONSTANT Constant;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::INDEX Index;
  typedef PkbTypes::VARIABLE Variable;
  typedef std::unordered_set<Constant> ConstantSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef std::shared_ptr<Cfg> CfgPtr;

  /**
   * Constructor for Pkb's write facade.
   *
   * @param pkb - Instance of Pkb.
   */
  explicit PkbWriteFacade(Pkb &pkb);

  /**
   * Destructor for Pkb's write facade.
   */
  ~PkbWriteFacade();

  /**
   * Adds variable into Pkb.
   *
   * @param variable - The target variable to add into Pkb.
   * @return The index of insertion.
   */
  Index AddVariable(const Variable &variable) const;

  /**
   *  Adds procedure into Pkb.
   *
   * @param procedure - The target procedure to add into Pkb.
   * @return The index of insertion.
   */
  Index AddProcedure(const Procedure &procedure) const;

  /**
   * Adds constant into Pkb.
   *
   * @param constant - The target constant to add into Pkb.
   * @return The index of insertion.
   */
  Index AddConstant(const Constant &constant) const;

  /**
   * Add uses relation side effects into Pkb.
   *
   * @param statement_number - The statement that is using a varaible.
   * @param variable - The variable that is being used.
   */
  void AddUsesSideEffects(const StatementNumber &statement_number, const Variable &variable) const;

  /**
   * Add modifies relation side effects into Pkb.
   *
   * @param statement_number - The statement that is modifying a varaible.
   * @param variable - The variable that is being modified.
   */
  void AddModifiesSideEffects(const StatementNumber &statement_number, const Variable &variable) const;

  /**
   * Adds a statement number and the corresponding variable being used into the Pkb.
   *
   * @param statement_number - The statement number to be added to the Pkb.
   * @param variable - The variable that is being used by the statement with the given statement number.
   */
  void AddStatementUsingVariable(const StatementNumber &statement_number,
                                 const Variable &variable) const;

  /**
   * Adds a statement number and the corresponding type of the statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of the statement.
   */
  void AddStatementOfAType(const StatementNumber &statement_number,
                           const StatementType &statement_type) const;

  /**
   * Adds a procedure and the corresponding variable being used into the Pkb.
   *
   * @param procedure - The procedure to be added to the Pkb.
   * @param variable - The variable that is being used within the given procedure.
   */
  void AddProcedureUsingVariable(const Procedure &procedure,
                                 const Variable &variable) const;

  /**
   * Adds a statement number and its corresponding modifying variable into Pkb.
   *
   * @param statement_number - The statement number to be added to the Pkb.
   * @param variable - The variable that is being modified by the statement with the given statement number.
   */
  void AddStatementModifyingVariable(const StatementNumber &statement_number,
                                     const Variable &variable) const;

  /**
   * Adds a procedure and its corresponding modifying variable into Pkb.
   *
   * @param procedure - The procedure to be added to the Pkb.
   * @param variable - The variable that is being modified within the given procedure.
   */
  void AddProcedureModifyingVariable(const Procedure &procedure,
                                     const Variable &variable) const;

  /**
   * Adds a follows relationship between two statements into the Pkb.
   *
   * @param statement_number_1 - The statement number of the first statement in the follows relationship.
   * @param statement_number_2 - The statement number of the second statement in the follows relationship.
   */
  void AddFollowsRelation(const StatementNumber &statement_number_1,
                          const StatementNumber &statement_number_2) const;

  /**
   * Add follows star relation to Pkb using the follows relations present.
   */
  void AddFollowsStarRelation() const;

  /**
   * Adds a parent relationship between two statements into the Pkb.
   *
   * @param statement_number_1 - The statement number of the first statement in the parent relationship.
   * @param statement_number_2 - The statement number of the second statement in the parent relationship.
   */
  void AddParentRelation(const StatementNumber &statement_number_1,
                         const StatementNumber &statement_number_2) const;

  /**
   * Add parent star relation to Pkb using the parent relations present.
   */
  void AddParentStarRelation() const;

  /**
   * Add expression side effects into Pkb like uses relationships.
   *
   * @param statement_number - The statement number the contains the expression.
   * @param expression - The expression in the statement.
   */
  void AddExpressionSideEffects(const StatementNumber &statement_number,
                                const ExpressionPtr &expression) const;

  /**
   * Adds an assignment statement and its expression into the Pkb.
   *
   * @param statement_number - The statement number of the assignment statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddAssignmentStatementAndExpression(const StatementNumber &statement_number,
                                           const ExpressionPtr &expression);

  /**
   * Adds an if statement and its condition into the Pkb.
   *
   * @param statement_number - The statement number of the if statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddIfStatementAndCondition(const StatementNumber &statement_number,
                                  const ExpressionPtr &expression);

  /**
   * Adds a while statement and its condition into the Pkb.
   *
   * @param statement_number - The statement number of the while statement.
   * @param expression - A shared pointer to the Expression object of the expression.
   */
  void AddWhileStatementAndCondition(const StatementNumber &statement_number,
                                     const ExpressionPtr &expression);

  /**
   * Adds calls relation to the Pkb.
   *
   * @param caller_procedure - The caller procedure.
   * @param callee_procedure - The callee procedure.
   */
  void AddCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure);

  /**
   * Add calls star relation to Pkb using the calls relations present.
   */
  void AddCallsStarRelation();

  /**
   * Adds calls statement to procedure name mapping to Pkb.
   *
   * @param statement_number - The statement number associated with the call statement.
   * @param procedure - The procedure being called as a part of that statement.
   */
  void AddCallStatementToProcedureName(const StatementNumber &statement_number, const Procedure &procedure);

  /**
   * Adds control flow graph to Pkb.
   *
   * @param cfg - The control flow graph to be added.
   */
  void AddCfg(const CfgPtr &cfg);
};

