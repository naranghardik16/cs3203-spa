#pragma once

#include "ClauseSyntax.h"
#include <utility>
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesSClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesSClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesPClauseEvaluator.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesPClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/AffectsClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/AffectsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/CallsClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/CallsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/NextClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/NextStarClauseEvaluator.h"

class SuchThatClauseSyntax : public ClauseSyntax {
 public:
  SuchThatClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other) override;
  bool IsBooleanClause(Map &declaration_map) override;
  std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Map &declaration_map) override;
};
