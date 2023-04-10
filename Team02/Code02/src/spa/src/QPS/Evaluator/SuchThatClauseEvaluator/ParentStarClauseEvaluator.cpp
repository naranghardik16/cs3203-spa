#include "ParentStarClauseEvaluator.h"

bool ParentStarClauseEvaluator::CheckIfReturnEmpty() {
  return (QueryUtil::IsSynonym(first_arg_) && !QueryUtil::IsContainerSynonym(first_arg_, declaration_map_)) ||
      QueryUtil::IsMatchingEntities(first_arg_, second_arg_);
}

bool ParentStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Parent*(_,_)
  return pkb_->IsAnyAncestorDescendantRelationshipPresent();
}

bool ParentStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Parent*(_,"5")
  return !pkb_->GetStatementsThatAreAncestorOf(second_arg_,
                                              StatementType::STATEMENT).empty();
}

bool ParentStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Parent*("5", _)
  return !pkb_->GetStatementsThatAreDescendantsOf(first_arg_,
                                                 StatementType::STATEMENT).empty();
}

bool ParentStarClauseEvaluator::HandleBothValue() {
  // Example query: Parent*(5, 6)
  return pkb_->HasAncestorDescendantRelationship(first_arg_, second_arg_);
}

ResultTable ParentStarClauseEvaluator::HandleBothSynonym() {
  // Example query: Parent*(a,p)
  return ConvertPairSetToResultTableFormat(pkb_->GetAncestorDescendantPairs(arg_1_type_, arg_2_type_));
}

ResultTable ParentStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Parent*(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreAncestors(arg_1_type_));
}

ResultTable ParentStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Parent*(a,"5")
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreAncestorOf(second_arg_, arg_1_type_));
}

ResultTable ParentStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Parent*(_, s)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreDescendants(arg_2_type_));
}

ResultTable ParentStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Parent*("5", a)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreDescendantsOf(first_arg_, arg_2_type_));
}
