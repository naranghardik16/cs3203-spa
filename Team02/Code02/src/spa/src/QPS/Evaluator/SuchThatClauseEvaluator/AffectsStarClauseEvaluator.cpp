#include "AffectsStarClauseEvaluator.h"

bool AffectsStarClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_an_invalid_syn = QueryUtil::IsSynonym(first_arg_)
      && !QueryUtil::IsAssignSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
  bool is_second_arg_an_invalid_syn = QueryUtil::IsSynonym(second_arg_)
      && !QueryUtil::IsAssignSynonym(declaration_map_, second_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, second_arg_);
  return is_first_arg_an_invalid_syn || is_second_arg_an_invalid_syn;
}

bool AffectsStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Affects*(_, _)
  return pkb_->IsThereAnyAffectsStarRelationship();
}

bool AffectsStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Affects*(_, 6)
  return !pkb_->GetAssignsAffectingStar(second_arg_).empty();
}

bool AffectsStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Affects*(6, _)
  return !pkb_->GetAssignsAffectedStarBy(first_arg_).empty();
}

bool AffectsStarClauseEvaluator::HandleBothValue() {
  // Example query: Affects*(6, 5)
  return pkb_->HasAffectsStarRelationship(first_arg_, second_arg_);
}

ResultTable AffectsStarClauseEvaluator::HandleBothSynonym() {
  // Example query: Affects(a, a1)
  PkbCommunicationTypes::PairConstraintSet pair_constraint = pkb_->GetAffectsStarPairs();

  if (is_same_syn_or_value_pairs_) {
    pair_constraint = ClauseEvaluator::FilterForSameSynonym(pair_constraint);
  }
  return ConvertPairSetToResultTableFormat(pair_constraint);
}

ResultTable AffectsStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Affects*(a, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAffectStar());
}

ResultTable AffectsStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Affects*(a,6)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectingStar(second_arg_));
}

ResultTable AffectsStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Affects*(_,a)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAreAffectedStar());
}

ResultTable AffectsStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Affects*(6, a)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectedStarBy(first_arg_));
}
