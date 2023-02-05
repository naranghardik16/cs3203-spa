#pragma once
#include "ClauseSyntax.h"

class SuchThatClauseSyntax : public ClauseSyntax {
 public:
  SuchThatClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other);
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Synonym s, Map &declaration_map, std::shared_ptr<PkbReadFacade> pkb);
};
