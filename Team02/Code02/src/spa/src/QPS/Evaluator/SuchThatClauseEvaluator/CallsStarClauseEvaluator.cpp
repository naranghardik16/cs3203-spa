#include "CallsStarClauseEvaluator.h"

bool CallsStarClauseEvaluator::CheckIfReturnEmpty() {
  return (first_arg_ == second_arg_) && !QueryUtil::IsWildcard(first_arg_);
}

bool CallsStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Calls*(_, _)
  return pkb_->IsThereAnyCallsStarRelationship();
}

bool CallsStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Calls*(_, “First”)
  return !pkb_->GetAllProceduresWithSpecifiedCalleeStar(QueryUtil::RemoveQuotations(second_arg_)).empty();
}

bool CallsStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Calls*("First", _)
  return !pkb_->GetAllProceduresWithSpecifiedCallerStar(QueryUtil::RemoveQuotations(first_arg_)).empty();
}

bool CallsStarClauseEvaluator::HandleBothValue() {
  // Example query: Calls*("First", "Second")
  return pkb_->HasCallsStarRelation(QueryUtil::RemoveQuotations(first_arg_), QueryUtil::RemoveQuotations(second_arg_));
}

ResultTable CallsStarClauseEvaluator::HandleBothSynonym() {
  // Example query: Calls*(p,q)
  return ConvertPairSetToResultTableFormat(pkb_->GetAllCallsStarPairs());
}

ResultTable CallsStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Calls*(p, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresThatAreCallersStar());
}

ResultTable CallsStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Calls*(p, “first”)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresWithSpecifiedCalleeStar(QueryUtil::RemoveQuotations(
      second_arg_)));
}

ResultTable CallsStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Calls*(_, p)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresThatAreCalleesStar());
}

ResultTable CallsStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Calls*(”first”, p)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresWithSpecifiedCallerStar(QueryUtil::RemoveQuotations(
      first_arg_)));
}
