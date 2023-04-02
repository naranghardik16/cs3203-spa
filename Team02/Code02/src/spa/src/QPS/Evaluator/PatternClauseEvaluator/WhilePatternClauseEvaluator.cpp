#include "WhilePatternClauseEvaluator.h"

ResultTable WhilePatternClauseEvaluator::HandleFirstArgSyn() {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetWhileConditionVariablePair());
}
ResultTable WhilePatternClauseEvaluator::HandleFirstArgWildcard() {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetWhileThatHasConditionVariable());
}

ResultTable WhilePatternClauseEvaluator::HandleFirstArgVariable()  {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetWhileWithConditionVariable(
      QueryUtil::RemoveQuotations(first_arg_)));
}

std::shared_ptr<Result> WhilePatternClauseEvaluator::HandlePartialMatch(const std::shared_ptr<Result>& r) {
  // impossible case
  return r;
}

std::shared_ptr<Result> WhilePatternClauseEvaluator::HandleExactMatch(const std::shared_ptr<Result>& r) {
  // impossible case
  return r;
}
