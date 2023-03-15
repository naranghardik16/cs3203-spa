#include "NextStarClauseEvaluator.h"

bool NextStarClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    // Example query: Next*(_, _)

    return pkb->HasNextStarRelationship();
  } else if (is_first_arg_a_wildcard) {
    // Example query: Next*(_, 1)

    return pkb->HasNextStarBy(second_arg_);
  } else if (is_second_arg_a_wildcard) {
    // Example query: Next*(1, _)

    return pkb->HasNextStar(first_arg_);
  } else {
    // Example query: Next*(1, 6)

    return pkb->IsNextStar(first_arg_, second_arg_);
  }
}

std::shared_ptr<Result> NextStarClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  ResultHeader header;
  ResultTable table;

  bool is_first_arg_synonym = declaration_map.count(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

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

  StatementType arg_1_type = QueryUtil::GetStatementType(declaration_map, first_arg_);
  StatementType arg_2_type = QueryUtil::GetStatementType(declaration_map, second_arg_);

  if (is_first_arg_synonym && is_second_arg_synonym) {
    // Example query: Next* (s,s)

    pair_constraint = pkb->GetNextStarPairs(arg_1_type, arg_2_type);
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    // Example query: Next* (s,_)

    single_constraint = pkb->GetNextStarFirst(arg_1_type);
  } else if (is_first_arg_synonym) {
    // Example query: Next* (s, 1)

    single_constraint = pkb->GetNextStarBy(second_arg_, arg_1_type);
  } else if (is_first_arg_a_wildcard) {
    // Example query: Next* (_, s)

    single_constraint = pkb->GetNextStarSecond(arg_2_type);
  } else {
    // Example query: Next* (1, s)

    single_constraint = pkb->GetNextStar(first_arg_, arg_2_type);
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

