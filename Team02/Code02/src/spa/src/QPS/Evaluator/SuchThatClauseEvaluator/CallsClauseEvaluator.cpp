#include "CallsClauseEvaluator.h"

bool CallsClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //Calls(_, _) : check if there are any calls relationship present
      return true;
    } else {
      //Calls(_, “First”) : get procedures that call the procedure First
      return true;
    }
  } else {
    if (is_second_arg_a_wildcard) {
      //Calls("First", _) : check if "First" calls any other procedures
      return true;
    } else {
      //Calls("First", "Second") : check if First calls Second
      return true;
    }
  }
}

std::shared_ptr<Result> CallsClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_ident = QueryUtil::IsQuoted(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultHeader header;
  if (is_first_arg_a_procedure_synonym) {
    header[first_arg_] = (int) header.size();
  }
  if (is_second_arg_a_procedure_synonym) {
    header[second_arg_] = (int) header.size();
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_first_arg_a_procedure_synonym) {
    if (is_second_arg_a_wildcard) {
      // Calls(p, _) --> Get procedures that call another procedure
      single_constraint = {};
    } else if (is_second_arg_a_procedure_synonym) {
      // Calls(p,q)
      pair_constraint = {};
    } else {
      //Calls(p, “first”) -- get procedures that call "First"
      single_constraint = {};
    }
  }

  if (is_first_arg_an_ident) {
    //e.g.Calls(”first”, p) --> get procedures called by "First"
    single_constraint = {};
  }

  if (is_first_arg_a_wildcard) {
    //e.g.Calls(_, p) --> get all procedures that are called
    single_constraint = {};
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
