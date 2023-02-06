#pragma once
#include "ParentClauseEvaluator.h"

bool ParentClauseEvaluator::IsBooleanConstraint() {
  return true;
}

bool ParentClauseEvaluator::EvaluateBooleanConstraint() {
  return true;
}

std::vector<std::vector<std::string>> ParentClauseEvaluator::EvaluateClause() {
  std::vector<std::vector<std::string>> set;
  return set;
}

