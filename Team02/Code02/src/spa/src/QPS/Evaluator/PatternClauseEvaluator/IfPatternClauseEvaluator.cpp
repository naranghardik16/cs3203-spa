#include "IfPatternClauseEvaluator.h"

ResultTable IfPatternClauseEvaluator::HandleFirstArgSyn() {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetIfConditionVariablePair());
}
ResultTable IfPatternClauseEvaluator::HandleFirstArgWildcard() {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetIfThatHasConditionVariable());
}

ResultTable IfPatternClauseEvaluator::HandleFirstArgVariable()  {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetIfWithConditionVariable(
      QueryUtil::RemoveQuotations(first_arg_)));
}

std::shared_ptr<Result> IfPatternClauseEvaluator::HandlePartialMatch(const std::shared_ptr<Result>& r) {
  // impossible case
  return r;
}

std::shared_ptr<Result> IfPatternClauseEvaluator::HandleExactMatch(const std::shared_ptr<Result>& r) {
  // impossible case
  return r;
}
