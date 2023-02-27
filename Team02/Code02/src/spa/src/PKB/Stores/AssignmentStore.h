#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

/**
 * @class AssignmentStore
 * Class representing Assignment Store in PKB.
 */
class AssignmentStore {
 public:
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
  void addAssignmentExpression(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  /**
   * Retrieves the expression of an assignment statement from the store.
   *
   * @param statement_number - The statement number of the assignment statement.
   * @return A shared pointer to the Expression object that represents the expression of the assignment statement.
   */
  std::shared_ptr<Expression> retrieveAssignmentExpressionByStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all statement numbers that contain a specific expression.
   *
   * @param expression - A shared pointer to the Expression object to search for.
   * @return An unordered set of statement numbers that contain the specified expression.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllStatementNumbersWhichContainExpression(std::shared_ptr<Expression> expression);

 private:
  // One-to-one store to store assignment statements' expressions.
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> assignment_store_;
};

