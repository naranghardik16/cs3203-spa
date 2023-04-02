#include "ParentStarClauseEvaluator.h"

bool ParentStarClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_not_a_container_syn = QueryUtil::IsSynonym(first_arg_)
      && !QueryUtil::IsIfSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsWhileSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
  bool is_same_syn_or_value_pairs = (first_arg_ == second_arg_) && !QueryUtil::IsWildcard(first_arg_);
  return is_first_arg_not_a_container_syn || is_same_syn_or_value_pairs;
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
