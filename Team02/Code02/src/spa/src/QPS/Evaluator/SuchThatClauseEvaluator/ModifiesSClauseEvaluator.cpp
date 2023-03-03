#pragma once
#include "ModifiesSClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool ModifiesSClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  //! first_arg is stmtref: If first arg is wildcard then semantic error; If first arg is synonym then it is not considered boolean constraint
  //! So first arg must be int
  //! Based on rule of boolean constraint, the 2nd arg cannot be a synonym so either wildcard or ident (since 2nd arg is entref)

  if (is_second_arg_a_wildcard) {
      //Modifies(5, _) -- does 5 modify any variables?
      return !pkb->GetVariablesModifiedByStatement(first_arg_).empty();
  } else {
    //Modifies(5, "count") -- does 5 modify "count"?
    return pkb->HasModifiesStatementRelationship(first_arg_, QueryUtil::GetIdent(second_arg_));
  }
}

std::shared_ptr<Result> ModifiesSClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  //!Validated in validator as a statement synonym or its subset
  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);

  //!Validated in validator as a variable synonym
  bool is_second_arg_a_variable_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_type_of_statement_synonym) {
    header[first_arg_] = (int) header.size();
  }
  if (is_second_arg_a_variable_synonym) {
    header[second_arg_] = (int) header.size();
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  //! Modifies Statement
  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Select s such that Modifies(s, _) / Select s1 such that Modifies(s1,_)
      // Should return the statements that have a Modifies relationship with any variable
      single_constraint = pkb->GetStatementsThatModify(QueryUtil::GetStatementType(declaration_map, first_arg_));
    } else if (is_second_arg_a_variable_synonym) {
      //e.g. Modifies(a,v)
      pair_constraint = pkb->GetModifiesStatementVariablePairs(QueryUtil::GetStatementType(declaration_map, first_arg_));
    } else {
      //e.g. Modifies(a,”count”) -- get assignments that modify count
      single_constraint = pkb->GetStatementsModifiesVariable(QueryUtil::GetIdent(second_arg_), QueryUtil::GetStatementType(declaration_map, first_arg_));
    }
  }

  //Second arg must be a synonym to not be boolean constraint
  if (is_first_arg_an_integer) {
    //e.g.Select v such that Modifies(5,v)
    single_constraint = pkb->GetVariablesModifiedByStatement(first_arg_);
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
