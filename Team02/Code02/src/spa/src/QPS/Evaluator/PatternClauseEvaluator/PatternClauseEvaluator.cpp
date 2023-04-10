#include "PatternClauseEvaluator.h"

bool PatternClauseEvaluator::EvaluateBooleanConstraint() {
  // Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> PatternClauseEvaluator::EvaluateClause() {
  ResultHeader header{{syn_, pql_constants::kResultTableInitialisationIndex}};
  ResultTable table;

  bool is_arg_1_synonym = declaration_map_.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  if (is_arg_1_synonym) {
    header[first_arg_] = static_cast<int>(header.size());
    table = HandleFirstArgSyn();
  } else if (is_arg_1_wildcard) {
    table = HandleFirstArgWildcard();
  } else {
    table = HandleFirstArgVariable();
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
