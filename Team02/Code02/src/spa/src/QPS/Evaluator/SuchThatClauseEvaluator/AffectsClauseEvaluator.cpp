#include "AffectsClauseEvaluator.h"

bool AffectsClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //Affects(_, _) : check if there are any affects relationship present
      return pkb->IsThereAnyAffectsRelationship();
    } else {
      //Affects(_, “6”) : get assigns that affect stmt 6
      return !pkb->GetAssignsAffecting(second_arg_).empty();
    }
  } else {
    if (is_second_arg_a_wildcard) {
      //Affects(6, _) : true if there are assigns that are affected by 6
      return !pkb->GetAssignsAffectedBy(first_arg_).empty();
    } else {
      //Affects("6, “5”) : check if 6 and 5 have an affects relationship
      return pkb->HasAffectsRelationship(first_arg_, second_arg_);
    }
  }
}

std::shared_ptr<Result> AffectsClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_type_of_assign_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_type_of_assign_synonym = QueryUtil::IsAssignSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_type_of_assign_synonym) {
    header[first_arg_] = (int) header.size();
  }
  if (is_second_arg_a_type_of_assign_synonym) {
    header[second_arg_] = (int) header.size();
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;
  if (is_first_arg_a_type_of_assign_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Affects(a, _) —> get all assign statements that affect any other assign statement
      single_constraint = pkb->GetAllAssignsThatAffect();
    } else if (is_second_arg_a_type_of_assign_synonym) {
      //e.g. Affects(a, a1) —> get pairs of assigns such that a affects a1
      pair_constraint = pkb->GetAffectsPairs();
    } else {
      //e.g. Affects(a,”6”) --> get assigns that affect stmt 6
      single_constraint = pkb->GetAssignsAffecting(second_arg_);
    }
  }

  //Second arg must be a synonym by rule of deciding non-boolean constraints
  if (is_first_arg_an_integer) {
    //e.g. Affects(”6”, a) --> Get all assignments that are affected by stmt 6
    single_constraint = pkb->GetAssignsAffectedBy(first_arg_);
  }

  //Second arg must be a synonym by rule of non-boolean constraints
  if (is_first_arg_a_wildcard) {
    //e.g. Affects(_,a) --> Get all assigns that are affected by any other assign statement
    single_constraint = pkb->GetAllAssignsThatAreAffected();
  }

  ResultTable table;
  if (!single_constraint.empty()) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
