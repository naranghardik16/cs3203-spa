#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class FollowsClauseEvaluator : public ClauseEvaluator {
 public:
  FollowsClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) : ClauseEvaluator(s,d,syntax_pair,pkb) {}
  std::vector<std::vector<std::string>> EvaluateClause();
};

