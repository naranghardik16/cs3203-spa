#pragma once
#include "QPS/Util/QueryUtil.h"
#include "PqlEvaluator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Evaluator/DesignEntityGetter.h"
#include <stdexcept>
#include <utility>

PqlEvaluator::PqlEvaluator(const std::shared_ptr<Query>& parser_output, std::shared_ptr<PkbReadFacade> pkb) {
  declaration_map_ = parser_output->GetDeclarationMap();
  synonym_tuple_ = parser_output->GetSynonymTuple();
  AdjustTrivialAttrRefs();
  syntax_list_ = parser_output->GetClauseSyntaxPtrList();
  is_return_empty_set_ = false;
  pkb_ = std::move(pkb);
}

void PqlEvaluator::AdjustTrivialAttrRefs() {
  //! remove trivial attr name e.g. r.stmt# is same as r
  for (int i = 0; i < synonym_tuple_.size(); ++i) {
    synonym_tuple_.at(i) = QueryUtil::AdjustTrivialAttrRefValue(synonym_tuple_[i], declaration_map_);
  }
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  if (synonym_tuple_.empty()) {
    return EvaluateBooleanQuery();
  }

  EvaluateBooleanConstraints();
  if (is_return_empty_set_) {
    return {};
  }

  if (syntax_list_.empty()) {
    auto evaluation_result = EvaluateSelectStatementWithoutClauses();
    return evaluation_result->ProjectResult(synonym_tuple_);
  }

  auto clause_evaluation_result = GetClauseEvaluationResult();
  if (is_return_empty_set_) {
    return {};
  }

  return GetFinalEvaluationResult(clause_evaluation_result);
}


std::unordered_set<std::string> PqlEvaluator::EvaluateBooleanQuery() {
  if (syntax_list_.size() == 0) {
    return {"TRUE"};
  }

  EvaluateBooleanConstraints();
  if (is_return_empty_set_) {
    return {"FALSE"};
  }
  if (syntax_list_.size() == 0) {
    return {"TRUE"};
  }

  auto clause_evaluation_result = GetClauseEvaluationResult();
  if (is_return_empty_set_ || clause_evaluation_result->table_.empty()) {
    return {"FALSE"};
  }
  return {"TRUE"};
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
        is_return_empty_set_ = true;
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
      is_return_empty_set_ = true;
      break;
    }
  }
  return clause_evaluation_result;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateSelectStatementWithoutClauses() {
  std::shared_ptr<Result> evaluation_result;

  auto first_syn = synonym_tuple_[0];
  evaluation_result = DesignEntityGetter::EvaluateBasicSelect(first_syn, pkb_, declaration_map_);
  auto &header = evaluation_result->header_;

  for (int i = 1; i < synonym_tuple_.size(); i++) {
    auto synonym = synonym_tuple_[i];
    if (std::find(header.begin(), header.end(), synonym) == header.end()) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(synonym, pkb_, declaration_map_);
      evaluation_result->JoinResult(initial_result);
    }
  }

  return evaluation_result;
}

std::unordered_set<string> PqlEvaluator::GetFinalEvaluationResult(std::shared_ptr<Result>& clause_evaluation_result) {
  if (synonym_tuple_.empty()) {
    return clause_evaluation_result->ProjectResultForBoolean();
  }


  //only add the remaining selected synonym values into table if it is not already present in the header
  auto &header = clause_evaluation_result->header_;
  for (int i = 0; i < synonym_tuple_.size(); i++) {
    auto synonym = synonym_tuple_[i];
    if (std::find(header.begin(), header.end(), synonym) == header.end()) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(synonym, pkb_, declaration_map_);
      clause_evaluation_result->JoinResult(initial_result);
    }
  }

  std::unordered_set<std::string> results;
  results = clause_evaluation_result->ProjectResult(synonym_tuple_);
  return results;
}