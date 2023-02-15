#pragma once
#include "FollowsStarClauseEvaluator.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool FollowsStarClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    //Example query: Follow*(_, _)

    return pkb->HasFollowsStarRelationship();
  } else if (is_first_arg_a_wildcard && !is_second_arg_a_wildcard) {
    //Example query: Follow*(_, 1)

    return pkb->HasFollowsStarBy(second_arg_);
  } else if (!is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    //Example query: Follow*(1, _)

    return pkb->HasFollowsStar(first_arg_);
  } else {
    //Example query: Follow*(1, 6)

    return pkb->IsFollowsStar(first_arg_, second_arg_);
  }
}

std::shared_ptr<Result> FollowsStarClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  ResultHeader header;
  ResultTable table;

  bool is_first_arg_synonym = declaration_map.count(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_synonym) {
    header.push_back(second_arg_);
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  StatementType arg_1_type = QueryUtil::GetStatementType(declaration_map, first_arg_);
  StatementType arg_2_type = QueryUtil::GetStatementType(declaration_map, second_arg_);

  if (is_first_arg_synonym && is_second_arg_synonym) {
    //Example query: Follows* (s,s)

    pair_constraint = pkb->GetFollowsStarPairs(arg_1_type, arg_2_type);
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    //Example query: Follows* (s,_)

    single_constraint = pkb->GetFollowsStarFirst(arg_1_type);
  } else if (is_first_arg_synonym) {
    //Example query: Follows* (s, 1)

    single_constraint = pkb->GetFollowsStarBy(second_arg_, arg_1_type);
  } else if (is_first_arg_a_wildcard) {
    //Example query: Follows* (_, s)

    single_constraint = pkb->GetFollowsStarSecond(arg_2_type);
  } else {
    //Example query: Follows* (1, s)

    single_constraint = pkb->GetFollowsStar(first_arg_, arg_2_type);
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
