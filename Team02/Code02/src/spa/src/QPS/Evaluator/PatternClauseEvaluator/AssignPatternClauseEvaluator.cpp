#include "AssignPatternClauseEvaluator.h"

bool AssignPatternClauseEvaluator::EvaluateBooleanConstraint() {
  // Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::EvaluateClause() {
  ResultHeader header{{syn_assign_, pql_constants::kResultTableInitialisationIndex}};
  ResultTable table;

  bool is_any_match = QueryUtil::IsWildcard(second_arg_);
  bool is_partial_match = QueryUtil::IsPartialMatchExpressionSpecification(second_arg_);

  bool is_arg_1_synonym = declaration_map_.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  if (is_arg_1_synonym) {
    header[first_arg_] = static_cast<int>(header.size());

    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetModifiesStatementVariablePairs
        (StatementType::ASSIGN));
  } else if (is_arg_1_wildcard) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetAssignStatements());
  } else {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetStatementsModifiesVariable(
        QueryUtil::RemoveQuotations(first_arg_), StatementType::ASSIGN));
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  if (is_any_match) {
    return result_ptr;
  } else if (is_partial_match) {
    return JoinWithAssignWithPartialExpression(result_ptr, pkb_);
  } else {
    return JoinWithAssignWithExactExpression(result_ptr, pkb_);
  }
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::JoinWithAssignWithPartialExpression(
    const std::shared_ptr<Result> &r,
    const std::shared_ptr<PkbReadFacade> &pkb) {
  ResultHeader header{{syn_assign_, 0}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb->GetAssignWithPartialExpression(
      expression_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::JoinWithAssignWithExactExpression(
    const std::shared_ptr<Result> &r, const std::shared_ptr<PkbReadFacade> &pkb) {
  ResultHeader header{{syn_assign_, pql_constants::kResultTableInitialisationIndex}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb->GetAssignWithExactExpression(
      expression_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}
