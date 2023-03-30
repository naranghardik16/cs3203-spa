#pragma once

#include "ClauseSyntax.h"
#include "QPS/Evaluator/WithClauseEvaluator/WithClauseEvaluator.h"

class WithClauseSyntax : public ClauseSyntax {
 public:
  WithClauseSyntax(const SyntaxPair& pair);
  bool Equals(ClauseSyntax &other) override;
  bool IsBooleanClause(Map &declaration_map) override;
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Map &declaration_map, std::shared_ptr<PkbReadFacade> pkb) override;
  int GetClauseScore(Map &declaration_map) override;
};
