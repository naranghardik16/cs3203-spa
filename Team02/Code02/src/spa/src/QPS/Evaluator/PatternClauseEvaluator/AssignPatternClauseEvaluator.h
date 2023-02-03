#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class AssignPatternClauseEvaluator : public ClauseEvaluator {
 public:
  AssignPatternClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair) : ClauseEvaluator(s,d,syntax_pair) {}
  PairConstraintSet EvaluateClause();
};
