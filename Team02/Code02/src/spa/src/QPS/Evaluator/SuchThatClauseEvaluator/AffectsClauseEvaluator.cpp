#include "AffectsClauseEvaluator.h"

bool AffectsClauseEvaluator::HandleBothWildcard() {
  // Example query: Affects(_, _)
  return pkb_->IsThereAnyAffectsRelationship();
}

bool AffectsClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Affects(_, 6)
  return !pkb_->GetAssignsAffecting(second_arg_).empty();
}

bool AffectsClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Affects(6, _)
  return !pkb_->GetAssignsAffectedBy(first_arg_).empty();
}

bool AffectsClauseEvaluator::HandleBothValue() {
  // Example query: Affects(6, 5)
  return pkb_->HasAffectsRelationship(first_arg_, second_arg_);
}

ResultTable AffectsClauseEvaluator::HandleBothSynonym() {
  if (!is_first_arg_a_valid_syn_ || !is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(a, a1)
  PkbCommunicationTypes::PairConstraintSet pair_constraint = pkb_->GetAffectsPairs();

  if (is_same_syn_or_value_pairs_) {
    pair_constraint = ClauseEvaluator::FilterForSameSynonym(pair_constraint);
  }
  return ConvertPairSetToResultTableFormat(pair_constraint);
}

ResultTable AffectsClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  if (!is_first_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(a, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAffect());
}

ResultTable AffectsClauseEvaluator::HandleFirstSynonymSecondValue() {
  if (!is_first_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(a,6)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffecting(second_arg_));
}

ResultTable AffectsClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  if (!is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(_,a)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAreAffected());
}

ResultTable AffectsClauseEvaluator::HandleFirstValueSecondSynonym() {
  if (!is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(6, a)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectedBy(first_arg_));
}
