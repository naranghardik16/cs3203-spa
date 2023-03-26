#include "FollowsStarClauseEvaluator.h"

bool FollowsStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Follows*(_,_)
  return pkb_->HasFollowsStarRelationship();
}

bool FollowsStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Follows*(_,"5")
  return pkb_->HasFollowsStarBy(second_arg_);
}

bool FollowsStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Follows*("5", _)
  return pkb_->HasFollowsStar(first_arg_);
}

bool FollowsStarClauseEvaluator::HandleBothValue() {
  if (is_same_syn_or_value_pairs_) {
    return false;
  }
  // Example query: Follows*(5, 6)
  return pkb_->IsFollowsStar(first_arg_, second_arg_);
}

ResultTable FollowsStarClauseEvaluator::HandleBothSynonym() {
  if (is_same_syn_or_value_pairs_) {
    return {};
  }
  // Example query: Follows*(a,p)
  return ConvertPairSetToResultTableFormat(pkb_->GetFollowsStarPairs(arg_1_type_, arg_2_type_));
}

ResultTable FollowsStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Follows*(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetFollowsStarFirst(arg_1_type_));
}

ResultTable FollowsStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Follows*(a,"5")
  return ConvertSetToResultTableFormat(pkb_->GetFollowsStarBy(second_arg_, arg_1_type_));
}

ResultTable FollowsStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Follows*(_, s)
  return ConvertSetToResultTableFormat(pkb_->GetFollowsStarSecond(arg_2_type_));
}

ResultTable FollowsStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Follows*("5", a)
  return ConvertSetToResultTableFormat(pkb_->GetFollowsStar(first_arg_, arg_2_type_));
}
