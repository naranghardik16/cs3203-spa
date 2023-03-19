#pragma once

#include "QPS/Query.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Evaluator/DesignEntityGetter.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Optimizer/Optimizer.h"
#include "QPS/Optimizer/ClauseGroup.h"
#include <utility>
#include <memory>

/**
 * Handles evaluation of PQL query by interacting with Pkb to get data
 */
class PqlEvaluator {
 private:
  SelectedSynonymTuple synonym_tuple_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_list_;
  bool is_return_empty_set_;
  std::shared_ptr<PkbReadFacade> pkb_;
  std::vector<std::shared_ptr<ClauseGroup>> groups_;

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
  unordered_set<string> GetFinalEvaluationResult(std::vector<std::shared_ptr<Result>>& clause_evaluation_results);
  std::vector<std::shared_ptr<Result>> GetClauseEvaluationResult();
  void EvaluateBooleanConstraints();
  shared_ptr<Result> EvaluateSelectStatementWithoutClauses();
  unordered_set<string> EvaluateBooleanQuery();
  void AdjustTrivialAttrRefs();
};
