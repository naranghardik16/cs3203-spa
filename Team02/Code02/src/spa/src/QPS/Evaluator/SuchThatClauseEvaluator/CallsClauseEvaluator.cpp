#include "CallsClauseEvaluator.h"

bool CallsClauseEvaluator::HandleBothWildcard() {
  // Example query: Calls(_, _)
  return pkb_->IsThereAnyCallsRelationship();
}

bool CallsClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Calls(_, “First”)
  return !pkb_->GetAllProceduresWithSpecifiedCallee(QueryUtil::GetIdent(second_arg_)).empty();
}

bool CallsClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Calls("First", _)
  return !pkb_->GetAllProceduresWithSpecifiedCaller(QueryUtil::GetIdent(first_arg_)).empty();
}

bool CallsClauseEvaluator::HandleBothValue() {
  // Example query: Calls("First", "Second")
  if (is_same_syn_or_value_pairs_) {
    return false;
  }
  return pkb_->HasCallsRelation(QueryUtil::GetIdent(first_arg_), QueryUtil::GetIdent(second_arg_));
}

ResultTable CallsClauseEvaluator::HandleBothSynonym() {
  // Example query: Calls(p,q)
  if (is_same_syn_or_value_pairs_) {
    return {};
  }
  return ConvertPairSetToResultTableFormat(pkb_->GetAllCallsPairs());
}

ResultTable CallsClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Calls(p, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresThatAreCallers());
}

ResultTable CallsClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Calls(p, “first”)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresWithSpecifiedCallee(QueryUtil::GetIdent(second_arg_)));
}

ResultTable CallsClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Calls(_, p)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresThatAreCallees());
}

ResultTable CallsClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Calls(”first”, p)
  return ConvertSetToResultTableFormat(pkb_->GetAllProceduresWithSpecifiedCaller(QueryUtil::GetIdent(first_arg_)));
}
