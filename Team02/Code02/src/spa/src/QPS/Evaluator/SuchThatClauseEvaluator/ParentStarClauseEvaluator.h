#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class ParentStarClauseEvaluator : public ClauseEvaluator {
 public:
  ParentStarClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) : ClauseEvaluator(s,d,syntax_pair,pkb) {}
  std::vector<std::vector<std::string>> EvaluateClause();
};
