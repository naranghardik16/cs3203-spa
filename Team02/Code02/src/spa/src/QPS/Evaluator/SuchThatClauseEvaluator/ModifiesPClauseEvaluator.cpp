#include "ModifiesPClauseEvaluator.h"

bool ModifiesPClauseEvaluator::HandleBothWildcard() {
  // Not possible
  return false;
}

bool ModifiesPClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Not possible
  return false;
}

bool ModifiesPClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Modifies("anya", _)
  return !pkb_->GetVariablesModifiedByProcedure(QueryUtil::GetIdent(first_arg_)).empty();
}

bool ModifiesPClauseEvaluator::HandleBothValue() {
  // Example query: Modifies("anya", "count")
  return pkb_->HasModifiesProcedureRelationship(QueryUtil::GetIdent(first_arg_), QueryUtil::GetIdent(second_arg_));
}

ResultTable ModifiesPClauseEvaluator::HandleBothSynonym() {
  // Example query: Modifies(p,v)
  return ConvertPairSetToResultTableFormat(pkb_->GetModifiesProcedureVariablePairs());
}

ResultTable ModifiesPClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Modifies(p, _)
  return ConvertSetToResultTableFormat(pkb_->GetProceduresThatModify());
}

ResultTable ModifiesPClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Modifies(p,”count”)
  return ConvertSetToResultTableFormat(pkb_->GetProceduresModifiesVariable(QueryUtil::GetIdent(second_arg_)));
}

ResultTable ModifiesPClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Not possible
  return {};
}

ResultTable ModifiesPClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Modifies("anya",v)
  return ConvertSetToResultTableFormat(pkb_->GetVariablesModifiedByProcedure(QueryUtil::GetIdent(first_arg_)));
}
