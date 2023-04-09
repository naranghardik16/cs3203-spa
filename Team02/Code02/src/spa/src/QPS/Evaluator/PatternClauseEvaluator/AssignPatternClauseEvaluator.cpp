#include "AssignPatternClauseEvaluator.h"

std::shared_ptr<Result> AssignPatternClauseEvaluator::EvaluateClause() {
  auto result_ptr = PatternClauseEvaluator::EvaluateClause();
  if (IsAnyMatch()) {
    return result_ptr;
  } else if (IsPartialMatch()) {
    return HandlePartialMatch(result_ptr);
  } else {
    return HandleExactMatch(result_ptr);
  }
}

bool AssignPatternClauseEvaluator::IsAnyMatch() {
  return QueryUtil::IsWildcard(second_arg_);
}

bool AssignPatternClauseEvaluator::IsPartialMatch() {
  return QueryUtil::IsPartialMatchExpressionSpecification(second_arg_);
}

ResultTable AssignPatternClauseEvaluator::HandleFirstArgSyn() {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb_->GetModifiesStatementVariablePairs
      (StatementType::ASSIGN));
}
ResultTable AssignPatternClauseEvaluator::HandleFirstArgWildcard() {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetAssignStatements());
}

ResultTable AssignPatternClauseEvaluator::HandleFirstArgVariable()  {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb_->GetStatementsModifiesVariable(
      QueryUtil::RemoveQuotations(first_arg_), StatementType::ASSIGN));
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::HandlePartialMatch(const std::shared_ptr<Result>& r) {
  ResultHeader header{{syn_, 0}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb_->GetAssignWithPartialExpression(
      expression_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::HandleExactMatch(const std::shared_ptr<Result>& r) {
  ResultHeader header{{syn_, pql_constants::kResultTableInitialisationIndex}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb_->GetAssignWithExactExpression(
      expression_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}
