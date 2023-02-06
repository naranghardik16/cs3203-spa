#pragma once
#include "ParentStarClauseEvaluator.h"

bool ParentStarClauseEvaluator::IsBooleanConstraint() {
  return true;
}

bool ParentStarClauseEvaluator::EvaluateBooleanConstraint() {
  return true;
}

std::vector<std::vector<std::string>>ParentStarClauseEvaluator::EvaluateClause() {
  std::vector<std::vector<std::string>> set;
  return set;
}