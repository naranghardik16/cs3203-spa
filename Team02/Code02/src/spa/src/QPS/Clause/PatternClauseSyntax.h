#pragma once

#include "ClauseSyntax.h"
#include "QPS/Evaluator/PatternClauseEvaluator/AssignPatternClauseEvaluator.h"

class PatternClauseSyntax : public ClauseSyntax {
 public:
  PatternClauseSyntax(SyntaxPair pair);
  void Accept(std::shared_ptr<Visitor> visitor) override;
  bool Equals(ClauseSyntax &other);
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Synonym s, Map declaration_map);
};
