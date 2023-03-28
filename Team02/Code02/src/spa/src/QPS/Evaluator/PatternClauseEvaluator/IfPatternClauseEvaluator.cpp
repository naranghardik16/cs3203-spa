#include "IfPatternClauseEvaluator.h"

bool IfPatternClauseEvaluator::EvaluateBooleanConstraint() {
  // Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> IfPatternClauseEvaluator::EvaluateClause() {
  ResultHeader header{{syn_if_, 0}};
  ResultTable table;

  bool is_arg_1_synonym = declaration_map_.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_arg_1_synonym) {
    // e.g. if(s, _, _)
    header[first_arg_] = static_cast<int>(header.size());

    pair_constraint = pkb_->GetIfConditionVariablePair();
  } else if (is_arg_1_wildcard) {
    // e.g. if(_,_,_)
    single_constraint = pkb_->GetIfThatHasConditionVariable();
  } else {
    single_constraint = pkb_->GetIfWithConditionVariable(QueryUtil::GetIdent(first_arg_));
  }

  if (!single_constraint.empty()) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
