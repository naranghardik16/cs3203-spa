#pragma once

#include "core/model/Expression.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class ControlFlowStore
 * Class representing Control Flow Store in Pkb.
 */
class ControlFlowStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef OneToOneStore<StatementNumber, ExpressionPtr> StatementNumberToExpressionStore;

  /**
   * Constructor for the ControlFlowStore
   */
  ControlFlowStore();

  /**
   * Destructor for the ControlFlowStore
   */
  ~ControlFlowStore();


  /**
   * Adds the statement number and condition expression to the store.
   *
   * @param statement_number - The statement number of the if statement.
   * @param expression - The condition expression of the if statement.
   */
  void AddIfStatementAndExpression(const StatementNumber& statement_number, const ExpressionPtr& expression);

  /**
   * Adds the statement number and condition expression to the store.
   *
   * @param statement_number - The statement number of the while statement.
   * @param expression - The condition expression of the while statement.
   */
  void AddWhileStatementAndExpression(const StatementNumber& statement_number, const ExpressionPtr& expression);

  /**
   * Retrieves the condition expression of the if statement with the given statement number.
   *
   * @param statement_number - The statement number of the if statement to retrieve.
   * @return The condition expression of the if statement.
   */
  ExpressionPtr GetExpressionFromIfStatement(const StatementNumber& statement_number);

  /**
   * Retrieves the condition expression of the while statement with the given statement number.
   *
   * @param statement_number - The statement number of the while statement to retrieve.
   * @return The condition expression of the while statement.
   */
  ExpressionPtr GetExpressionFromWhileStatement(const StatementNumber& statement_number);

  /**
   * Retrieves all statement numbers of the if statements with the given condition expression.
   *
   * @param expression - The condition expression to retrieve the if statement numbers for.
   * @return The set of all statement numbers of the if statements with the given condition expression.
   */
  StatementNumberSet
  GetIfStatementsFromExpression(const ExpressionPtr& expression);

  /**
   * Retrieve all statement numbers of the while statements with the given condition expression.
   *
   * @param expression - The condition expression to retrieve the while statement numbers for.
   * @return The set of all statement numbers of the while statements with the given condition expression.
   */
  StatementNumberSet
  GetWhileStatementsFromExpression(const ExpressionPtr& expression);

 private:
  // Map statement numbers to condition expressions for if and while statements.
  StatementNumberToExpressionStore if_store_;
  StatementNumberToExpressionStore while_store_;
};

