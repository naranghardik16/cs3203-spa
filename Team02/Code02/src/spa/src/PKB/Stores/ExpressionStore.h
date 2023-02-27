#pragma once

#include <unordered_set>
#include "core/model/Expression.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"

/**
 * @class ExpressionStore
 * Class representing Expression store in PKB.
 */
class ExpressionStore {
 public:
  /**
   * Constructor for Expression store.
   */
  ExpressionStore();

  /**
   * Destructor for Expression store.
   */
  ~ExpressionStore();

  /**
   * Adds an expression to the store.
   * @param expression - A shared pointer to the Expression object to be added.
   */
  void addExpression(std::shared_ptr<Expression> expression);

  /**
   * Retrieves the set of variables used in a given expression.
   *
   * @param expression - A shared pointer to the Expression object to be queried.
   * @return An unordered set of variables used in the given expression.
   */
  std::unordered_set<PkbTypes::VARIABLE> retrieveVariablesOfTheExpression(
      std::shared_ptr<Expression> expression);

  /**
   * Retrieves the set of constants used in a given expression.
   *
   * @param expression - A shared pointer to the Expression object to be queried.
   * @return An unordered set of constants used in the given expression.
   */
  std::unordered_set<PkbTypes::CONSTANT> retrieveConstantsOfTheExpression(
      std::shared_ptr<Expression> expression);

 private:
  // Stores the mapping between an expression and set of variables used in it.
  OneToManyStore<std::shared_ptr<Expression>, PkbTypes::VARIABLE>
      expression_to_variable_store_;
  // Stores the mapping between an expression and the set of constants used in it.
  OneToManyStore<std::shared_ptr<Expression>, PkbTypes::CONSTANT>
      expression_to_constant_store_;
};

