#include "UsesSClauseEvaluator.h"

bool UsesSClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_second_arg_a_wildcard) {
    //Example query: Uses(5, _)

    //TODO: PKB call
    return true;
  } else {
    //Example query: uses(5, "count")
    //TODO: PKB call
    return true;
  }
}

std::shared_ptr<Result> UsesSClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_synonym = declaration_map.count(first_arg_);
  bool is_second_arg_synonym = declaration_map.count(second_arg_);

  if (is_first_arg_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_synonym) {
    header.push_back(second_arg_);
  }

  SingleConstraintSet single_constraint;
  PairConstraintSet pair_constraint;

  if (is_first_arg_synonym && is_second_arg_synonym) {
    //Example query: Uses(s, v)

    //TODO: PKB call
  } else if (is_first_arg_synonym) {
    //Example query: Uses(s, _) or Uses(s, "x")

    //TODO: PKB call
  } else {
    //Example query: Uses(1, v)

    //TODO: PKB call
  }

  if (!single_constraint.empty()) {
    table = QueryUtil::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = QueryUtil::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
