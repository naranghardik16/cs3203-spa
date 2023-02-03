#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class FollowsClauseEvaluator : public ClauseEvaluator {
 public:
  FollowsClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};

