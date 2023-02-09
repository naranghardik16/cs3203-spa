#pragma once
#include "ModifiesClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool ModifiesClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  //! first_arg is stmtref: If first arg is wildcard then semantic error; If first arg is synonym then it is not considered boolean constraint
  //! So first arg is either ident or int
  //! Based on rule of boolean constraint, the 2nd arg cannot be a synonym so either wildcard or ident (since 2nd arg is entref)

  if (is_first_arg_an_integer) {
    if (is_second_arg_a_wildcard) {
      //Modifies(5, _) -- does 5 modify any variables?
      return !pkb->GetVariablesModifiedByStatement(first_arg_).empty();
    } else {
      //Modifies(5, "count") -- does 5 modify "count"?
      return pkb->HasModifiesStatementRelationship(first_arg_, second_arg_);
    }
  } else {
    if (is_second_arg_a_wildcard) {
      //Modifies("anya", _) -- does the procedure anya modify any variables?
      return !pkb->GetVariablesModifiedByProcedure(first_arg_).empty();
    } else {
      //Modifies("anya", "count") -- does the procedure anya modify "count"?
      return pkb->HasModifiesProcedureRelationship(first_arg_, second_arg_);
    }
  }
}

std::shared_ptr<Result> ModifiesClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  //!Validated in validator as a statement synonym or its subset
  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);

  bool is_first_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_ident = QueryUtil::IsQuoted(first_arg_);

  //!Validated in validator as a variable synonym
  bool is_second_arg_a_variable_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_type_of_statement_synonym || is_first_arg_a_procedure_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_a_variable_synonym) {
    header.push_back(second_arg_);
  }

  SingleConstraintSet single_constraint;
  PairConstraintSet pair_constraint;

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
      single_constraint = pkb->GetStatementsModifiesVariable(second_arg_, QueryUtil::GetStatementType(declaration_map, first_arg_));
    }
  }

  //Second arg must be a synonym to not be boolean constraint
  if (is_first_arg_an_integer) {
    //e.g.Select v such that Modifies(5,v)
    single_constraint = pkb->GetVariablesModifiedByStatement(first_arg_);
  }

  //! Modifies Procedure
  if (is_first_arg_a_procedure_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Select p such that Modifies(p, _) / Select p1 such that Modifies(p1,_)
      // Should return the procedure that have a Modifies relationship with any variable
      single_constraint = pkb->GetProceduresThatModify();
    } else if (is_second_arg_a_variable_synonym) {
      //e.g. Modifies(p,v)
      pair_constraint = pkb->GetModifiesProcedureVariablePairs();
    } else {
      //e.g. Modifies(p,”count”) -- get procedures that modify count
      single_constraint = pkb->GetProceduresModifiesVariable(second_arg_);
    }
  }

  if (is_first_arg_an_ident) {
    //e.g.Select v such that Modifies("anya",v)
    single_constraint = pkb->GetVariablesModifiedByProcedure(first_arg_);
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