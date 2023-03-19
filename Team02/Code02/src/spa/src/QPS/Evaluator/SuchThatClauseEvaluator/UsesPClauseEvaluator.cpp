#include "UsesPClauseEvaluator.h"

bool UsesPClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_second_arg_a_wildcard) {
    // Example query: Uses("Main", _)

    return !pkb->GetVariablesUsedByProcedure(QueryUtil::GetIdent(first_arg_)).empty();
  } else {
    // Example query: uses("Main", "count")

    return pkb->HasUsesProcedureRelationship(QueryUtil::GetIdent(first_arg_), QueryUtil::GetIdent(second_arg_));
  }
}

std::shared_ptr<Result> UsesPClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_synonym = declaration_map.count(first_arg_);

  bool is_second_arg_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_synonym) {
    header[first_arg_] = static_cast<int>(header.size());
  }
  if (is_second_arg_synonym) {
    header[second_arg_] = static_cast<int>(header.size());
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_first_arg_synonym && is_second_arg_synonym) {
    // Example query: Uses(p, v)

    pair_constraint = pkb->GetUsesProcedureVariablePairs();
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    // Example query: Uses(p, _)

    single_constraint = pkb->GetProceduresThatUse();
  } else if (is_first_arg_synonym && !is_second_arg_a_wildcard) {
    // Example query: Uses(p, "x")

    single_constraint = pkb->GetProceduresUsesVariable(QueryUtil::GetIdent(second_arg_));
  } else {
    // Example query: Uses("Main", v)

    single_constraint = pkb->GetVariablesUsedByProcedure(QueryUtil::GetIdent(first_arg_));
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
