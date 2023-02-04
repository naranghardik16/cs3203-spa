#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class FollowsStarClauseEvaluator : public ClauseEvaluator {
 public:
  FollowsStarClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};
