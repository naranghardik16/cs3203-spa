#pragma once
#include "QPS/Query.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include <memory>

/**
 * Handles evaluation of PQL query by interacting with PKB to get data
 */
class PqlEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_pair_list_;
  std::shared_ptr<PkbReadFacade> pkb_;

 public:
  PqlEvaluator(const std::shared_ptr<Query>& parser_output, std::shared_ptr<PkbReadFacade> pkb);

  /**
   * Evaluates a query based on the parsed query output from parser
   * @return final evaluation result in the form of unordered set of strings
   */
  std::unordered_set<std::string> Evaluate();

  /**
   * Evaluates a basic Select statement without subclauses
   * @return Result class, which stores the evaluation information for handling in Evaluator
   */
  std::shared_ptr<Result> EvaluateBasicSelectStatement();

  /**
   * Checks if a clause has any synonyms in its arguments as if there are no synonyms then this clause will not have dependencies
   * with other subclauses and can be handled in a simpler manner
   * @param a SyntaxPair containing information about the arguments of the subclause
   * @return true if the clause has no synonyms in its arguments
   */
  bool IsBooleanConstraint(const SyntaxPair& pair);
};
