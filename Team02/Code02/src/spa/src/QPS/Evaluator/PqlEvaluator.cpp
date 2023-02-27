#pragma once
#include "QPS/Util/QueryUtil.h"
#include "PqlEvaluator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Evaluator/DesignEntityGetter.h"
#include <stdexcept>
#include <utility>

PqlEvaluator::PqlEvaluator(const std::shared_ptr<Query>& parser_output, std::shared_ptr<PkbReadFacade> pkb) {
  synonym_tuple_ = parser_output->GetSynonymTuple();
  syntax_list_ = parser_output->GetClauseSyntaxPtrList();
  declaration_map_ = parser_output->GetDeclarationMap();
  is_return_empty_set = false;
  pkb_ = std::move(pkb);
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  //! Process boolean constraints first
  EvaluateBooleanConstraints();
  if (is_return_empty_set) {
    return {};
  }

  if (syntax_list_.size() == 0) {
    if (synonym_tuple_.empty()) {
      return {"True"};
    }
    auto evaluation_result = EvaluateSelectStatementWithoutClauses();
    return evaluation_result->ProjectResult(synonym_tuple_);
  }

  auto clause_evaluation_result = GetClauseEvaluationResult();
  if (is_return_empty_set) {
    return {};
  }

  return GetFinalEvaluationResult(clause_evaluation_result);
}

void PqlEvaluator::EvaluateBooleanConstraints() {
  //!Evaluate and remove all boolean constraints first
  for (int i=0; i<syntax_list_.size(); i++) {
    auto clause = syntax_list_[i];
    auto is_bool_constraint = clause->IsBooleanClause(declaration_map_);

    if (is_bool_constraint) {
      auto evaluator = clause->CreateClauseEvaluator(declaration_map_);
      auto is_clause_true = evaluator->EvaluateBooleanConstraint(pkb_);
      if (!is_clause_true) {
        is_return_empty_set = true;
      }
      syntax_list_.erase(syntax_list_.begin() + i);
    }
  }
}

std::shared_ptr<Result> PqlEvaluator::GetClauseEvaluationResult() {
  std::shared_ptr<Result> clause_evaluation_result;
  auto first_clause = syntax_list_[0];
  clause_evaluation_result = first_clause->CreateClauseEvaluator(declaration_map_)->EvaluateClause(pkb_);
  //Evaluate the remaining constraints and use intersection of result classes to resolve constraints
  for (int i = 1; i < syntax_list_.size(); i++) {
    auto kClause = syntax_list_[i];
    auto evaluator = kClause->CreateClauseEvaluator(declaration_map_);
    std::shared_ptr<Result> intermediate_result = evaluator->EvaluateClause(pkb_);

    //get intersection
    clause_evaluation_result->JoinResult(intermediate_result);

    //Whenever results become empty stop and return empty set
    if (clause_evaluation_result->table_.empty()) {
      is_return_empty_set = true;
      break;
    }
  }
  return clause_evaluation_result;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateSelectStatementWithoutClauses() {
  std::shared_ptr<Result> evaluation_result;

  auto first_syn = synonym_tuple_[0];
  evaluation_result = EvaluateBasicSelect(first_syn);

  for (int i = 1; i < synonym_tuple_.size(); i++) {
    auto synonym = synonym_tuple_[i];
    if (std::find(synonym_tuple_.begin(), synonym_tuple_.end(), synonym) == synonym_tuple_.end()) {
      auto initial_result = EvaluateBasicSelect(synonym);
      evaluation_result->JoinResult(initial_result);
    }
  }

  return evaluation_result;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateBasicSelect(Synonym synonym) {
  ResultHeader header;
  header.push_back(synonym);
  ResultTable table = ClauseEvaluator::ConvertSetToResultTableFormat(
      DesignEntityGetter::GetEntitySet(pkb_, declaration_map_[synonym]));

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

std::unordered_set<string> PqlEvaluator::GetFinalEvaluationResult(std::shared_ptr<Result> clause_evaluation_result) {
  if (synonym_tuple_.empty()) {
    //!return clause_evaluation_result->ProjectResultForBoolean();
  }


  //only add the remaining selected synonym values into table if it is not already present in the header
  auto header = clause_evaluation_result->header_;
  for (int i = 0; i < synonym_tuple_.size(); i++) {
    auto synonym = synonym_tuple_[i];
    if (std::find(header.begin(), header.end(), synonym) == header.end()) {
      auto initial_result = EvaluateBasicSelect(synonym);
      clause_evaluation_result->JoinResult(initial_result);
    }
  }

  std::unordered_set<std::string> results;
  results = clause_evaluation_result->ProjectResult(synonym_tuple_);
  return results;
}