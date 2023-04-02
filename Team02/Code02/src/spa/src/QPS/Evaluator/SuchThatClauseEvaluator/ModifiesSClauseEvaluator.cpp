#include "ModifiesSClauseEvaluator.h"

bool ModifiesSClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_a_type_of_print_synonym = QueryUtil::IsSynonym(first_arg_)
      && QueryUtil::IsPrintSynonym(declaration_map_, first_arg_);
  return is_first_arg_a_type_of_print_synonym;
}

bool ModifiesSClauseEvaluator::HandleBothWildcard() {
  // Not possible
  return false;
}

bool ModifiesSClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Not possible
  return false;
}

bool ModifiesSClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Modifies(5, _)
  return !pkb_->GetVariablesModifiedByStatement(first_arg_).empty();
}

bool ModifiesSClauseEvaluator::HandleBothValue() {
  // Example query: Modifies(5, "count")
  return pkb_->HasModifiesStatementRelationship(first_arg_,
                                                QueryUtil::RemoveQuotations(second_arg_));
}

ResultTable ModifiesSClauseEvaluator::HandleBothSynonym() {
  // Example query: Modifies(a,v)
  return ConvertPairSetToResultTableFormat(pkb_->GetModifiesStatementVariablePairs(arg_1_type_));
}

ResultTable ModifiesSClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Modifies(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatModify(arg_1_type_));
}

ResultTable ModifiesSClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Modifies(a,”count”)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsModifiesVariable(QueryUtil::RemoveQuotations(second_arg_),
                                                                           arg_1_type_));
}

ResultTable ModifiesSClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Not possible
  return {};
}

ResultTable ModifiesSClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Modifies(5,v)
  return ConvertSetToResultTableFormat(pkb_->GetVariablesModifiedByStatement(first_arg_));
}
