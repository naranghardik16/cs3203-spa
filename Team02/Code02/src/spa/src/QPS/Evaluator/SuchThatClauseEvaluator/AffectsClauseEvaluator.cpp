#include "AffectsClauseEvaluator.h"

bool AffectsClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_an_invalid_syn = QueryUtil::IsSynonym(first_arg_)
      && !QueryUtil::IsAssignSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
  bool is_second_arg_an_invalid_syn = QueryUtil::IsSynonym(second_arg_)
      && !QueryUtil::IsAssignSynonym(declaration_map_, second_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, second_arg_);
  return is_first_arg_an_invalid_syn || is_second_arg_an_invalid_syn;
}

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
  // Example query: Affects(a, a1)
  PkbCommunicationTypes::PairConstraintSet pair_constraint = pkb_->GetAffectsPairs();

  if (is_same_syn_or_value_pairs_) {
    pair_constraint = ClauseEvaluator::FilterForSameSynonym(pair_constraint);
  }
  return ConvertPairSetToResultTableFormat(pair_constraint);
}

ResultTable AffectsClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Affects(a, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAffect());
}

ResultTable AffectsClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Affects(a,6)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffecting(second_arg_));
}

ResultTable AffectsClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Affects(_,a)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAreAffected());
}

ResultTable AffectsClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Affects(6, a)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectedBy(first_arg_));
}
