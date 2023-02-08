#pragma once
#include "ModifiesProcedureClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool ModifiesProcedureClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  //! first_arg is entref: If first arg is wildcard then semantic error; If first arg is synonym then it is not considered boolean constraint
  //! first arg must be IDENT
  //! Based on rule of boolean constraint, the 2nd arg cannot be a synonym
  if (is_second_arg_a_wildcard) {
    //Modifies("anya", _) -- does the procedure anya modify any variables?
    return !pkb->GetVariablesModifiedByProcedure(first_arg_).empty();
  } else {
    //Modifies("anya", "count") -- does the procedure anya modify "count"?
    return pkb->HasModifiesProcedureRelationship(first_arg_, second_arg_);
  }
}

std::shared_ptr<Result> ModifiesProcedureClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  //!Validated in validator as a statement synonym or its subset
  bool is_first_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, first_arg_);
  bool is_first_arg_a_call_synonym = QueryUtil::IsCallSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_ident = QueryUtil::IsQuoted(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  //!Validated in validator as a variable synonym
  bool is_second_arg_a_variable_synonym = declaration_map.count(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_procedure_synonym || is_first_arg_a_call_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_a_variable_synonym) {
    header.push_back(second_arg_);
  }

  SingleConstraintSet single_constraint;
  PairConstraintSet pair_constraint;

  //!Validated in validator: First arg cannot be _ as this is semantic error
  if (is_first_arg_a_procedure_synonym || is_first_arg_a_call_synonym) {
        if (is_second_arg_a_wildcard) {
          //e.g. Select p such that Modifies(p, _) / Select p1 such that Modifies(p1,_)
          // Should return the procedure that have a Modifies relationship with any variable
          single_constraint = pkb->GetProceduresThatModify(is_first_arg_a_call_synonym);
        } else if (is_second_arg_a_variable_synonym) {
          //e.g. Modifies(p,v)
          pair_constraint = pkb->GetModifiesProcedureVariablePairs(is_first_arg_a_call_synonym);
        } else {
          //e.g. Modifies(p,”count”) -- get procedures that modify count
          single_constraint = pkb->GetProceduresModifiesVariable(second_arg_, is_first_arg_a_call_synonym);
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