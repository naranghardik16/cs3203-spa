#include "WhilePatternClauseEvaluator.h"

bool WhilePatternClauseEvaluator::EvaluateBooleanConstraint() {
  // Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> WhilePatternClauseEvaluator::EvaluateClause() {
  ResultHeader header{{syn_while_, pql_constants::kResultTableInitialisationIndex}};
  ResultTable table;

  bool is_arg_1_synonym = declaration_map_.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  if (is_arg_1_synonym) {
    // e.g. while(s,_)
    header[first_arg_] = static_cast<int>(header.size());
    table =  ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetWhileConditionVariablePair());
  } else if (is_arg_1_wildcard) {
    // e.g. while(_,_)
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetWhileThatHasConditionVariable());
  } else {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetWhileWithConditionVariable(
        QueryUtil::RemoveQuotations
            (first_arg_)));
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
