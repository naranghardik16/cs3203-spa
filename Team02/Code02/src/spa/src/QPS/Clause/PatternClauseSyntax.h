#pragma once

#include "ClauseSyntax.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/PatternClauseEvaluator/AssignPatternClauseEvaluator.h"
#include "QPS/Evaluator/PatternClauseEvaluator/IfPatternClauseEvaluator.h"
#include "QPS/Evaluator/PatternClauseEvaluator/WhilePatternClauseEvaluator.h"

class PatternClauseSyntax : public ClauseSyntax {
 public:
  PatternClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other) override;
  bool IsBooleanClause(Map &declaration_map) override;
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Map &declaration_map, std::shared_ptr<PkbReadFacade> pkb) override;
  int GetClauseScore(Map &declaration_map) override;
};
