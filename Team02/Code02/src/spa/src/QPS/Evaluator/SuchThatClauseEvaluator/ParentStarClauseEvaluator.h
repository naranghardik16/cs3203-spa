#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class ParentStarClauseEvaluator : public ClauseEvaluator {
 public:
  ParentStarClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};
