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
