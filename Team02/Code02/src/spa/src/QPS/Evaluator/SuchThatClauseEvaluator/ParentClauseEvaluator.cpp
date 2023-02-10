#pragma once
#include "ParentClauseEvaluator.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool ParentClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultTable table;

  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //e.g. Parent(_,_) -- return all Parent-Child relationships between statements
      return pkb->IsAnyParentRelationshipPresent();
    } else {
      //e.g. Parent(_,"5") --> Get all types of statements that "5" is child of
      return !pkb->GetStatementThatIsParentOf(second_arg_, StatementType::STATEMENT).empty();
    }
  } else {
    //! Must be an integer since the definition of Boolean constraint is no synonyms
    if (is_second_arg_a_wildcard) {
      //e.g. Parent("5", _) --> Get all types of statements that are child of"5"
      return !pkb->GetStatementsThatAreChildrenOf(first_arg_, StatementType::STATEMENT).empty();
    } else {
      //e.g. Parent(5, 6) --> Check if 5 is parent of 6
      return pkb->HasParentChildRelationship(first_arg_, second_arg_);
    }
  }
}

std::shared_ptr<Result> ParentClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_type_of_statement_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_a_type_of_statement_synonym) {
    header.push_back(second_arg_);
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;
  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Parent(s, _) --> Get statements that are parents
      single_constraint = pkb->GetStatementsThatAreParents(QueryUtil::GetStatementType(declaration_map, first_arg_));
    } else if (is_second_arg_a_type_of_statement_synonym) {
      //e.g. Parent(a,p) --> get (assign stmt parent, print stmt child) pairs
      pair_constraint = pkb->GetParentChildPairs(QueryUtil::GetStatementType(declaration_map, first_arg_), QueryUtil::GetStatementType(declaration_map, second_arg_));
    } else {
      //e.g. Parent(a,"5") --> Get assign statement that is parent of 5
      single_constraint = pkb->GetStatementThatIsParentOf(second_arg_, QueryUtil::GetStatementType(declaration_map, first_arg_));
    }
  }

  //Second arg must be a synonym by rule of deciding non-boolean constraints
  if (is_first_arg_an_integer) {
    //e.g. Parent("5", a) --> Get assign statements that are children of 5
    single_constraint = pkb->GetStatementsThatAreChildrenOf(first_arg_, QueryUtil::GetStatementType(declaration_map, second_arg_));
  }

  //Second arg must be a synonym by rule of non-boolean constraints
  if (is_first_arg_a_wildcard) {
    //e.g. Parent(_, s) --> Get statements are child of any other statement
    single_constraint = pkb->GetStatementsThatAreChildren(QueryUtil::GetStatementType(declaration_map, second_arg_));
  }

  ResultTable table;
  if (!single_constraint.empty()) {
    table = QueryUtil::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = QueryUtil::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
