#include "UsesPClauseEvaluator.h"

bool UsesPClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_second_arg_a_wildcard) {
    //Example query: Uses("Main", _)

    //TODO: PKB call
    return true;
  } else {
    //Example query: uses("Main", "count")

    //TODO: PKB call
    return true;
  }
}

std::shared_ptr<Result> UsesPClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
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
    //Example query: Uses(p, v)

    //TODO: PKB call
  } else if (is_first_arg_synonym) {
    //Example query: Uses(p, _) or Uses(p, "x")

    //TODO: PKB call
  } else {
    //Example query: Uses("Main", v)

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
