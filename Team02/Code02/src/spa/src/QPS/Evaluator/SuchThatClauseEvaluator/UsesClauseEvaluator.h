#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class UsesClauseEvaluator : public ClauseEvaluator {
 public:
  UsesClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};
