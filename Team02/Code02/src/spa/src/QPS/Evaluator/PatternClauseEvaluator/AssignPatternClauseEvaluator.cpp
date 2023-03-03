#include "AssignPatternClauseEvaluator.h"

bool AssignPatternClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  //Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header{{syn_assign_, 0}};
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_any_match = QueryUtil::IsWildcard(second_arg_);
  bool is_partial_match = QueryUtil::IsPartialMatchExpressionSpecification(second_arg_);

  bool is_arg_1_synonym = declaration_map.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_arg_1_synonym) {
    header[first_arg_] = (int) header.size();

    pair_constraint = pkb->GetModifiesStatementVariablePairs(StatementType::ASSIGN);
  } else if (is_arg_1_wildcard) {
    single_constraint = pkb->GetAssignStatements();
  } else {
    single_constraint = pkb->GetStatementsModifiesVariable(QueryUtil::GetIdent(first_arg_), StatementType::ASSIGN);
  }

  if (!single_constraint.empty()) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  if (is_any_match) {
    return result_ptr;
  } else if (is_partial_match) {
    return JoinWithAssignWithPartialExpression(result_ptr, pkb);
  } else {
    return JoinWithAssignWithExactExpression(result_ptr, pkb);
  }
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::JoinWithAssignWithPartialExpression(std::shared_ptr<Result> r,
                                                                                          std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header{{syn_assign_, 0}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb->GetAssignWithPartialExpression(second_arg_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}

std::shared_ptr<Result> AssignPatternClauseEvaluator::JoinWithAssignWithExactExpression(std::shared_ptr<Result> r,
                                                                                        std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header{{syn_assign_, 0}};
  ResultTable table;

  PkbCommunicationTypes::SingleConstraintSet single_constraint = pkb->GetAssignWithExactExpression(second_arg_);
  table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  result_ptr->JoinResult(r);

  return result_ptr;
}
