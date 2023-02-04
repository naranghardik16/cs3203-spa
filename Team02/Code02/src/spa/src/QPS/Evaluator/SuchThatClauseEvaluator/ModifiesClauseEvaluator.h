#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class ModifiesClauseEvaluator : public ClauseEvaluator {
 public:
  ModifiesClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};