#pragma once

#include "ClauseSyntax.h"
#include "QPS/Evaluator/PatternClauseEvaluator/AssignPatternClauseEvaluator.h"

class PatternClauseSyntax : public ClauseSyntax {
 public:
  PatternClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other);
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Synonym s, Map declaration_map);
};
