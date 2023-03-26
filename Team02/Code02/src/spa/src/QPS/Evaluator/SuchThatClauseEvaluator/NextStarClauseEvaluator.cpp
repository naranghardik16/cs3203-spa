#include "NextStarClauseEvaluator.h"

bool NextStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Next*(_, _)
  return pkb_->HasNextStarRelationship();
}

bool NextStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Next*(_, 1)
  return pkb_->HasNextStarBy(second_arg_);
}

bool NextStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Next*(1, _)
  return pkb_->HasNextStar(first_arg_);
}

bool NextStarClauseEvaluator::HandleBothValue() {
  // Example query: Next*(1, 6)
  return pkb_->IsNextStar(first_arg_, second_arg_);
}

ResultTable NextStarClauseEvaluator::HandleBothSynonym() {
  PkbCommunicationTypes::PairConstraintSet pair_constraint = pkb_->GetNextStarPairs(arg_1_type_, arg_2_type_);

  if (is_same_syn_or_value_pairs_) {
    pair_constraint = ClauseEvaluator::FilterForSameSynonym(pair_constraint);
  }
  // Example query: Next* (s,s)
  return ConvertPairSetToResultTableFormat(pair_constraint);
}

ResultTable NextStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Next* (s,_)
  return ConvertSetToResultTableFormat(pkb_->GetNextStarFirst(arg_1_type_));
}

ResultTable NextStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Next* (s, 1)
  return ConvertSetToResultTableFormat(pkb_->GetNextStarBy(second_arg_, arg_1_type_));
}

ResultTable NextStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Next* (_, s)
  return ConvertSetToResultTableFormat(pkb_->GetNextStarSecond(arg_2_type_));
}

ResultTable NextStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Next* (1, s)
  return ConvertSetToResultTableFormat(pkb_->GetNextStar(first_arg_, arg_2_type_));
}
