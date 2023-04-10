#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::CheckIfReturnEmpty() {
  return QueryUtil::IsMatchingEntities(first_arg_, second_arg_);
}

bool FollowsClauseEvaluator::HandleBothWildcard() {
  // Example query: Follows(_,_)
  return pkb_->IsAnyFollowsRelationshipPresent();
}

bool FollowsClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Follows(_,"5")
  return !pkb_->GetStatementFollowedBy(second_arg_, StatementType::STATEMENT).empty();
}

bool FollowsClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Follows("5", _)
  return !pkb_->GetStatementFollowing(first_arg_, StatementType::STATEMENT).empty();
}

bool FollowsClauseEvaluator::HandleBothValue() {
  // Example query: Follows(5, 6)
  return pkb_->HasFollowsRelationship(first_arg_, second_arg_);
}

ResultTable FollowsClauseEvaluator::HandleBothSynonym() {
  // Example query: Follows(a,p)
  return ConvertPairSetToResultTableFormat(pkb_->GetFollowPairs(arg_1_type_, arg_2_type_));
}

ResultTable FollowsClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Follows(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsWithFollowers(arg_1_type_));
}

ResultTable FollowsClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Follows(a,"5")
  return ConvertSetToResultTableFormat(pkb_->GetStatementFollowedBy(second_arg_, arg_1_type_));
}

ResultTable FollowsClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Follows(_, s)
  return ConvertSetToResultTableFormat(pkb_->GetStatementThatAreFollowers(arg_2_type_));
}

ResultTable FollowsClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Follows("5", a)
  return ConvertSetToResultTableFormat(pkb_->GetStatementFollowing(first_arg_, arg_2_type_));
}
