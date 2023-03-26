#include "UsesSClauseEvaluator.h"

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
                                           QueryUtil::GetIdent(second_arg_));
}

ResultTable UsesSClauseEvaluator::HandleBothSynonym() {
  if (is_first_arg_a_read_synonym_) {
    return {};
  }
  // Example query: Uses(s, v)
  return ConvertPairSetToResultTableFormat(pkb_->GetUsesStatementVariablePairs(arg_1_type_));
}

ResultTable UsesSClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  if (is_first_arg_a_read_synonym_) {
    return {};
  }
  // Example query: Uses(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatUses(arg_1_type_));
}

ResultTable UsesSClauseEvaluator::HandleFirstSynonymSecondValue() {
  if (is_first_arg_a_read_synonym_) {
    return {};
  }
  // Example query: Uses(s, "x")
  return ConvertSetToResultTableFormat(pkb_->GetStatementsUsesVariable(arg_1_type_,
                                                                       QueryUtil::GetIdent(second_arg_)));
}

ResultTable UsesSClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Not possible
  return {};
}

ResultTable UsesSClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Uses(1, v)
  return ConvertSetToResultTableFormat(pkb_->GetVariablesUsedByStatement(first_arg_));
}
