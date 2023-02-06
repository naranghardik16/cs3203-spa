#pragma once
#include "ModifiesClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool ModifiesClauseEvaluator::IsBooleanConstraint() {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  auto is_first_arg_a_procedure_call = LexicalRuleValidator::IsIdent(first_arg_)
      && !QueryUtil::IsProcedureSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_ident = LexicalRuleValidator::IsIdent(second_arg_) && !is_second_arg_a_variable_synonym;

  //e.g. Modifies("anya",”count”) or Modifies(5, "count)
  return ((is_first_arg_an_integer && is_second_arg_a_ident) || is_first_arg_a_procedure_call && is_second_arg_a_ident);
}

bool ModifiesClauseEvaluator::EvaluateBooleanConstraint() {
  auto pkb = ClauseEvaluator::GetPKB();
  auto is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool result;
  if (is_first_arg_an_integer) {
    result = pkb->IsModifiesStatement(first_arg_, second_arg_);
  } else {
    result = pkb->IsModifiesProcedure(first_arg_, second_arg_);
  }
  return result;
}

std::vector<std::vector<std::string>> ModifiesClauseEvaluator::EvaluateClause() {
  auto syntax_pair = ClauseEvaluator::GetSyntaxPair();
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto pkb = ClauseEvaluator::GetPKB();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg_) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);
  bool is_first_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, second_arg_);
  bool is_first_arg_a_call_synonym = QueryUtil::IsCallSynonym(declaration_map, second_arg_);
  bool is_first_arg_a_procedure_name = LexicalRuleValidator::IsIdent(first_arg_) && !is_first_arg_a_procedure_synonym
      && !is_first_arg_a_call_synonym;

  std::vector<std::vector<std::string>> result;

  //! Evaluate Statements
  if (is_first_arg_a_type_of_statement_synonym) {
    auto type = declaration_map[first_arg_];
    //e.g. Modifies(a,v)
    if (is_second_arg_a_variable_synonym) {
      result = pkb->GetModifiesStatementVariablePairs(type);
    } else if (is_second_arg_a_wildcard) {
      //e.g. Modifies(a, _) --> get all assignments that are modified
      auto constraints = pkb->GetModifiesStatementVariablePairs(type);
      result = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else {
      //e.g. Modifies(a,”count”) -- get assignments that modify count
        result = pkb->GetStatementsModifiesVariable(second_arg_, type);
      }
  }

  if (is_first_arg_an_integer) {
    //e.g. Modifies(5, _)
    if (is_second_arg_a_wildcard) {
      result = pkb->GetVariablesModifiedByStatement(first_arg_);
    }
    if (is_second_arg_a_variable_synonym) {
      //e.g. Modifies(5,v)
      result = pkb->GetVariablesModifiedByStatement(first_arg_);
    }
  }

  //! Evaluate Procedures
  if (is_first_arg_a_procedure_synonym || is_first_arg_a_call_synonym) {
    //e.g. Modifies(p,v), Modifies(c,v)
    if (is_second_arg_a_variable_synonym) {
      result = pkb->GetModifiesProcedureVariablePairs(is_first_arg_a_call_synonym);
    } else if (is_second_arg_a_wildcard) {
      //e.g. Modifies(p, _) --> get all procedures that are modified, Modifies(c, _)
      auto constraints = pkb->GetModifiesProcedureVariablePairs(is_first_arg_a_call_synonym);
      result = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else {
      //e.g. Modifies(p,”count”) -- get procedures that modify count,  Modifies(c, "count")
      result = pkb->GetProceduresModifiesVariable(second_arg_, is_first_arg_a_call_synonym);
    }
  }

  if (is_first_arg_a_procedure_name) {
    //e.g. Modifies("anya", v)
    if (is_second_arg_a_variable_synonym) {
      result = pkb->GetVariablesModifiedByProcedure(first_arg_);
    }
    if (is_second_arg_a_wildcard) {
      //e.g. Modifies("anya", _)
      result = pkb->GetVariablesModifiedByProcedure(first_arg_);
    }
  }

  return result;
}