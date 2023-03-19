#pragma once

#include <unordered_set>

#include "core/model/Expression.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class ExpressionStore
 * Class representing Expression store in Pkb.
 *
 * The ExpressionStore class is responsible for storing all expressions in Pkb and provides methods for querying
 * variables and constants used in a particular expression.
 */
class ExpressionStore {
 public:
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::CONSTANT Constant;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Constant> ConstantSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef OneToManyStore<ExpressionPtr, Variable> ExpressionToMultiVariableStore;
  typedef OneToManyStore<ExpressionPtr, Constant> ExpressionToMultiConstantStore;

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
  void AddExpression(const ExpressionPtr& expression);

  /**
   * Retrieves the set of variables used in a given expression.
   *
   * @param expression - A shared pointer to the Expression object to be queried.
   * @return An unordered set of variables used in the given expression.
   */
  VariableSet GetVariablesFromExpression(const ExpressionPtr& expression);

  /**
   * Retrieves the set of constants used in a given expression.
   *
   * @param expression - A shared pointer to the Expression object to be queried.
   * @return An unordered set of constants used in the given expression.
   */
  ConstantSet GetConstantsFromExpression(const ExpressionPtr& expression);

 private:
  // Stores the mapping between an expression and set of variables used in it.
  ExpressionToMultiVariableStore expression_to_variable_store_;
  // Stores the mapping between an expression and the set of constants used in it.
  ExpressionToMultiConstantStore expression_to_constant_store_;
};

