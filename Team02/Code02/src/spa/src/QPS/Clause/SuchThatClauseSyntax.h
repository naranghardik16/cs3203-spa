#pragma once
#include "ClauseSyntax.h"

class SuchThatClauseSyntax : public ClauseSyntax {
 public:
  SuchThatClauseSyntax(SyntaxPair pair);
  void Accept(std::shared_ptr<Visitor> visitor) override;
  bool Equals(ClauseSyntax &other);
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Synonym s, Map declaration_map);
};
