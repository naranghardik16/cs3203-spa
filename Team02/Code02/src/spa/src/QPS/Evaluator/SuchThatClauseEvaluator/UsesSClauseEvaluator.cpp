#include "UsesSClauseEvaluator.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool UsesSClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_second_arg_a_wildcard) {
    //Example query: Uses(5, _)

    return !pkb->GetVariablesUsedByStatement(first_arg_).empty();
  } else {
    //Example query: uses(5, "count")

    return pkb->HasUsesStatementRelationship(first_arg_, QueryUtil::GetIdent(second_arg_));
  }
}

std::shared_ptr<Result> UsesSClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_synonym = declaration_map.count(first_arg_);

  bool is_second_arg_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_synonym) {
    header[first_arg_] = header.size();
  }
  if (is_second_arg_synonym) {
    header[second_arg_] = header.size();
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  StatementType arg_1_type = QueryUtil::GetStatementType(declaration_map, first_arg_);

  if (is_first_arg_synonym && is_second_arg_synonym) {
    //Example query: Uses(s, v)

    pair_constraint = pkb->GetUsesStatementVariablePairs(arg_1_type);
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    //Example query: Uses(s, _)

    single_constraint = pkb->GetStatementsThatUses(arg_1_type);
  } else if (is_first_arg_synonym) {
    //Example query: Uses(s, "x")

    single_constraint = pkb->GetStatementsUsesVariable(arg_1_type, QueryUtil::GetIdent(second_arg_));
  } else {
    //Example query: Uses(1, v)

    single_constraint = pkb->GetVariablesUsedByStatement(first_arg_);
  }

  if (!single_constraint.empty()) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
