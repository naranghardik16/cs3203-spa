#include "UsesSClauseEvaluator.h"

bool UsesSClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_a_read_synonym = QueryUtil::IsSynonym(first_arg_)
      && QueryUtil::IsReadSynonym(declaration_map_, first_arg_);
  return is_first_arg_a_read_synonym;
}

bool UsesSClauseEvaluator::HandleBothWildcard() {
  // Not possible
  return false;
}

bool UsesSClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Not possible
  return false;
}

bool UsesSClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Uses(5, _)
  return !pkb_->GetVariablesUsedByStatement(first_arg_).empty();
}

bool UsesSClauseEvaluator::HandleBothValue() {
  // Example query: uses(5, "count")
  return pkb_->HasUsesStatementRelationship(first_arg_,
                                            QueryUtil::RemoveQuotations(second_arg_));
}

ResultTable UsesSClauseEvaluator::HandleBothSynonym() {
  // Example query: Uses(s, v)
  return ConvertPairSetToResultTableFormat(pkb_->GetUsesStatementVariablePairs(arg_1_type_));
}

ResultTable UsesSClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Uses(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatUses(arg_1_type_));
}

ResultTable UsesSClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Uses(s, "x")
  return ConvertSetToResultTableFormat(pkb_->GetStatementsUsesVariable(arg_1_type_,
                                                                       QueryUtil::RemoveQuotations(second_arg_)));
}

ResultTable UsesSClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Not possible
  return {};
}

ResultTable UsesSClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Uses(1, v)
  return ConvertSetToResultTableFormat(pkb_->GetVariablesUsedByStatement(first_arg_));
}
