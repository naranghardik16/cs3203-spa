#pragma once
#include "UsesClauseEvaluator.h"

bool UsesClauseEvaluator::IsBooleanConstraint() {
  return true;
}

bool UsesClauseEvaluator::EvaluateBooleanConstraint() {
  return true;
}

std::vector<std::vector<std::string>> UsesClauseEvaluator::EvaluateClause() {
  std::vector<std::vector<std::string>> set;
  return set;
}