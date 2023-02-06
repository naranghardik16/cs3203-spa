#pragma once
#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::IsBooleanConstraint() {
  return true;
}
bool FollowsClauseEvaluator::EvaluateBooleanConstraint() {
  return true;
}

std::vector<std::vector<std::string>> FollowsClauseEvaluator::EvaluateClause() {
  std::vector<std::vector<std::string>> set;
  return set;
}

