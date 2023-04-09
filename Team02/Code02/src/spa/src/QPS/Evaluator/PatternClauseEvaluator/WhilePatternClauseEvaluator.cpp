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
