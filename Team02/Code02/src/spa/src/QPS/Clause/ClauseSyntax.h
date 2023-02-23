#pragma once

#include <string>
#include <memory>
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Evaluator/ClauseEvaluator.h"
#include "PKB/Interfaces/PkbReadFacade.h"

/*
 * Factory class that creates ClauseEvaluators for evaluation of queries
 */
class ClauseSyntax {
 private:
  SyntaxPair pair_;
 public:
  explicit ClauseSyntax(SyntaxPair pair);

  /**
   * Gets the entity from the SyntaxPair, which is a relationship reference in Such That clause or a syn-assign in Pattern clause
   * @return the entity as a string
   */
  std::string GetEntity();

  /**
   * Returns the first argument in the subclause
   * @return first argument as a string
   */
  std::string GetFirstParameter();

  /**
  * Returns the second argument in the subclause
  * @return second argument as a string
  */
  std::string GetSecondParameter();

  /**
   * Returns the whole SyntaxPair
   * @return SyntaxPair stored as attribute
   */
  SyntaxPair GetSyntaxPair();

  virtual bool Equals(ClauseSyntax &other) = 0;

  virtual bool IsBooleanClause(Map &declaration_map) = 0;

  /**
   * Creates ClauseEvaluators for evaluation of PQL queries using factory design pattern
   * @param s synonym that is to be selected
   * @param declaration_map which contains synonyms as keys and corresponding design entity as value
   * @return a ClauseEvaluator for the specific subclause
   */
  virtual std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Map &declaration_map) = 0;
};
