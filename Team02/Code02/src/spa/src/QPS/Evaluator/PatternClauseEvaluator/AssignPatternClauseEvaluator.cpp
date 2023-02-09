#include "AssignPatternClauseEvaluator.h"

bool AssignPatternClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  //Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_second_arg_underscore = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_exact_expr = second_arg_[0] != '_';

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
