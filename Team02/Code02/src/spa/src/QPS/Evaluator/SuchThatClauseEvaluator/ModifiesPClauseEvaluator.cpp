#include "ModifiesPClauseEvaluator.h"

#pragma once
#include "ModifiesSClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool ModifiesPClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  //! So first arg must be ident since first arg can either be syn (non-boolean constraint) or int (falls under ModifiesS)
  //! Based on rule of boolean constraint, the 2nd arg cannot be a synonym so either wildcard or ident (since 2nd arg is entref)
  if (is_second_arg_a_wildcard) {
      //Modifies("anya", _) -- does the procedure anya modify any variables?
      return !pkb->GetVariablesModifiedByProcedure(QueryUtil::GetIdent(first_arg_)).empty();
  } else {
      //Modifies("anya", "count") -- does the procedure anya modify "count"?
      return pkb->HasModifiesProcedureRelationship(QueryUtil::GetIdent(first_arg_), QueryUtil::GetIdent(second_arg_));
  }
}

std::shared_ptr<Result> ModifiesPClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_ident = QueryUtil::IsQuoted(first_arg_);

  //!Validated in validator as a variable synonym
  bool is_second_arg_a_variable_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_procedure_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_a_variable_synonym) {
    header.push_back(second_arg_);
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

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
      single_constraint = pkb->GetProceduresModifiesVariable(QueryUtil::GetIdent(second_arg_));
    }
  }

  if (is_first_arg_an_ident) {
    //e.g.Select v such that Modifies("anya",v)
    single_constraint = pkb->GetVariablesModifiedByProcedure(QueryUtil::GetIdent(first_arg_));
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
