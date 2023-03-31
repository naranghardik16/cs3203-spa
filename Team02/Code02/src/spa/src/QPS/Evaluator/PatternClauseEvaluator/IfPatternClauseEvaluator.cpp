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

  if (is_arg_1_synonym) {
    // e.g. if(s, _, _)
    header[first_arg_] = static_cast<int>(header.size());
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetIfConditionVariablePair());
  } else if (is_arg_1_wildcard) {
    // e.g. if(_,_,_)
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetIfThatHasConditionVariable());
  } else {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetIfWithConditionVariable(
        QueryUtil::RemoveQuotations(first_arg_)));
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
