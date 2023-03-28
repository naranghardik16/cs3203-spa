#include "UsesPClauseEvaluator.h"

bool UsesPClauseEvaluator::HandleBothWildcard() {
  // Not possible
  return false;
}

bool UsesPClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Not possible
  return false;
}

bool UsesPClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Uses("Main", _)
  return !pkb_->GetVariablesUsedByProcedure(QueryUtil::GetIdent(first_arg_)).empty();
}

bool UsesPClauseEvaluator::HandleBothValue() {
  // Example query: Uses("Main", "x")
  return pkb_->HasUsesProcedureRelationship(QueryUtil::GetIdent(first_arg_), QueryUtil::GetIdent(second_arg_));
}

ResultTable UsesPClauseEvaluator::HandleBothSynonym() {
  // Example query: Uses(p, v)
  return ConvertPairSetToResultTableFormat(pkb_->GetUsesProcedureVariablePairs());
}

ResultTable UsesPClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Uses(p, _)
  return ConvertSetToResultTableFormat(pkb_->GetProceduresThatUse());
}

ResultTable UsesPClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Uses(p, "x")
  return ConvertSetToResultTableFormat(pkb_->GetProceduresUsesVariable(QueryUtil::GetIdent(second_arg_)));
}

ResultTable UsesPClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Not possible
  return {};
}

ResultTable UsesPClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Uses("Main", v)
  return ConvertSetToResultTableFormat(pkb_->GetVariablesUsedByProcedure(QueryUtil::GetIdent(first_arg_)));
}
