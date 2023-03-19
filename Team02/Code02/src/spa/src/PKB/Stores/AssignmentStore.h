#pragma once

#include "core/model/Expression.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class AssignmentStore
 * Class representing Assignment Store in Pkb.
 */
class AssignmentStore {
 public:
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef OneToOneStore<StatementNumber, ExpressionPtr> StatementNumberToExpressionStore;

  /**
   * Constructor for Assignment Store.
   */
  AssignmentStore();

  /**
   * Destructor for Assignment Store.
   */
  ~AssignmentStore();

  /**
   * Adds the expression of an assignment statement to the store.
   *
   * @param statement_number - The statement number of the assignment statement.
   * @param expression - A shared pointer to the Expression object that represents the expression of the assignment
   * statement.
   */
  void AddAssignmentExpression(const StatementNumber& statement_number, const ExpressionPtr& expression);

  /**
   * Retrieves the expression of an assignment statement from the store.
   *
   * @param statement_number - The statement number of the assignment statement.
   * @return A shared pointer to the Expression object that represents the expression of the assignment statement.
   */
  ExpressionPtr GetExpressionFromStatementNumber(const StatementNumber& statement_number);

  /**
   * Retrieves all statement numbers that contain a specific expression.
   *
   * @param expression - A shared pointer to the Expression object to search for.
   * @return An unordered set of statement numbers that contain the specified expression.
   */
  StatementNumberSet GetStatementNumbersFromExpression(const ExpressionPtr& expression);

 private:
  // One-to-one store to store assignment statements' expressions.
  StatementNumberToExpressionStore statement_number_to_expression_store_;
};

