#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class ParentClauseEvaluator : public ClauseEvaluator {
 public:
  ParentClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};
