#include "NextClauseEvaluator.h"

bool NextClauseEvaluator::CheckIfReturnEmpty() {
  return QueryUtil::IsMatchingEntities(first_arg_, second_arg_);
}

bool NextClauseEvaluator::HandleBothWildcard() {
  // Example query: Next(_, _)
  return pkb_->HasNextRelationship();
}

bool NextClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Next(_, 1)
  return pkb_->HasNextBy(second_arg_);
}

bool NextClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Next(1, _)
  return pkb_->HasNext(first_arg_);
}

bool NextClauseEvaluator::HandleBothValue() {
  // Example query: Next(1, 6)
  return pkb_->IsNext(first_arg_, second_arg_);
}

ResultTable NextClauseEvaluator::HandleBothSynonym() {
  // Example query: Next (s,s)
  return ConvertPairSetToResultTableFormat(pkb_->GetNextPairs(arg_1_type_, arg_2_type_));
}

ResultTable NextClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Next (s,_)
  return ConvertSetToResultTableFormat(pkb_->GetNextFirst(arg_1_type_));
}

ResultTable NextClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Next (s, 1)
  return ConvertSetToResultTableFormat(pkb_->GetNextBy(second_arg_, arg_1_type_));
}

ResultTable NextClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Next (_, s)
  return ConvertSetToResultTableFormat(pkb_->GetNextSecond(arg_2_type_));
}

ResultTable NextClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Next (1, s)
  return ConvertSetToResultTableFormat(pkb_->GetNext(first_arg_, arg_2_type_));
}
