#pragma once
#include "FollowsClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"


bool FollowsClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(_,_) -- return all Follows relationships between statements
      return pkb->IsAnyFollowsRelationshipPresent();
    } else {
      //e.g. Follows(_,"5") --> Get all types of statements that "5" follows
      return !pkb->GetStatementFollowedBy(second_arg_, StatementType::STATEMENT).empty();
    }
  } else {
    //! Must be an integer since the definition of Boolean constraint is no synonyms
    if (is_second_arg_a_wildcard) {
      //e.g. Follows("5", _) --> Get all types of statements that follow "5"
      return !pkb->GetStatementFollowing(first_arg_, StatementType::STATEMENT).empty();
    } else {
      //e.g. Follows(5, 6)
      return pkb->HasFollowsRelationship(first_arg_, second_arg_);
    }
  }
}


std::shared_ptr<Result> FollowsClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_type_of_statement_synonym) {
    header[first_arg_] = header.size();
  }
  if (is_second_arg_a_type_of_statement_synonym) {
    header[second_arg_] = header.size();
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;
  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(s, _) --> Get statements that have followers
      single_constraint = pkb->GetStatementsWithFollowers(QueryUtil::GetStatementType(declaration_map, first_arg_));
    } else if (is_second_arg_a_type_of_statement_synonym) {
      //e.g. Follows(a,p)
      pair_constraint = pkb->GetFollowPairs(QueryUtil::GetStatementType(declaration_map, first_arg_), QueryUtil::GetStatementType(declaration_map, second_arg_));
    } else {
      //e.g. Follows(a,"5") --> Get statement that 5 follows of type assignment
      single_constraint =
          pkb->GetStatementFollowedBy(second_arg_, QueryUtil::GetStatementType(declaration_map, first_arg_));
    }
  }

  //Second arg must be a synonym by rule of deciding non-boolean constraints
  if (is_first_arg_an_integer) {
    //e.g. Follows("5", a) --> Get statement that follow 5 of type assignment
    single_constraint =
        pkb->GetStatementFollowing(first_arg_, QueryUtil::GetStatementType(declaration_map, second_arg_));
  }

  //Second arg must be a synonym by rule of non-boolean constraints
  if (is_first_arg_a_wildcard) {
    //e.g. Follows(_, s) --> Get statements that follow another statement
    single_constraint = pkb->GetStatementThatAreFollowers(QueryUtil::GetStatementType(declaration_map, second_arg_));
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

