#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

/**
 * @class ControlFlowStore
 * Class representing Control Flow Store in PKB.
 */
class ControlFlowStore {
 public:
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
  void addIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  /**
   * Adds the statement number and condition expression to the store.
   *
   * @param statement_number - The statement number of the while statement.
   * @param expression - The condition expression of the while statement.
   */
  void addWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number, std::shared_ptr<Expression> expression);

  /**
   * Retrieves the condition expression of the if statement with the given statement number.
   *
   * @param statement_number - The statement number of the if statement to retrieve.
   * @return The condition expression of the if statement.
   */
  std::shared_ptr<Expression> retrieveIfStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves the condition expression of the while statement with the given statement number.
   *
   * @param statement_number - The statement number of the while statement to retrieve.
   * @return The condition expression of the while statement.
   */
  std::shared_ptr<Expression> retrieveWhileStatementCondition(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all statement numbers of the if statements with the given condition expression.
   *
   * @param expression - The condition expression to retrieve the if statement numbers for.
   * @return The set of all statement numbers of the if statements with the given condition expression.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllIfStatementsWithCondition(std::shared_ptr<Expression> expression);

  /**
   * Retrieve all statement numbers of the while statements with the given condition expression.
   *
   * @param expression - The condition expression to retrieve the while statement numbers for.
   * @return The set of all statement numbers of the while statements with the given condition expression.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER>
  retrieveAllWhileStatementsWithCondition(std::shared_ptr<Expression> expression);

 private:
  // Map statement numbers to condition expressions for if and while statements.
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> if_store_;
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<Expression>> while_store_;
};

