#include "PqlEvaluator.h"

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
    synonym_tuple_.at(i) = QueryUtil::AdjustSynonymWithTrivialAttrRefValue(synonym_tuple_[i], declaration_map_);
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
  if (syntax_list_.empty()) {
    return {"TRUE"};
  }

  EvaluateBooleanConstraints();
  if (is_return_empty_set_) {
    return {"FALSE"};
  }
  if (syntax_list_.empty()) {
    return {"TRUE"};
  }

  auto clause_evaluation_result = GetClauseEvaluationResult();
  if (is_return_empty_set_ || clause_evaluation_result->table_.empty()) {
    return {"FALSE"};
  }
  return {"TRUE"};
}

void PqlEvaluator::EvaluateBooleanConstraints() {
  // Evaluate and remove all boolean constraints first

  for (auto iter = syntax_list_.begin(); iter != syntax_list_.end(); ) {
    auto clause = *iter;
    auto is_bool_constraint = clause->IsBooleanClause(declaration_map_);

    if (is_bool_constraint) {
      auto evaluator = clause->CreateClauseEvaluator(declaration_map_);
      auto is_clause_true = evaluator->EvaluateBooleanConstraint(pkb_);
      if (!is_clause_true) {
        is_return_empty_set_ = true;
      }
      iter = syntax_list_.erase(iter);
    } else {
      ++iter;
    }
  }
}

std::shared_ptr<Result> PqlEvaluator::GetClauseEvaluationResult() {
  std::shared_ptr<Result> clause_evaluation_result = std::make_shared<Result>(ResultHeader{}, ResultTable{});

  // Evaluate the remaining constraints and use intersection of result classes to resolve constraints
  for (const auto& kClause : syntax_list_) {
    auto evaluator = kClause->CreateClauseEvaluator(declaration_map_);
    std::shared_ptr<Result> intermediate_result = evaluator->EvaluateClause(pkb_);

    // get intersection
    clause_evaluation_result->JoinResult(intermediate_result);

    // Whenever results become empty stop and return empty set
    if (clause_evaluation_result->table_.empty()) {
      is_return_empty_set_ = true;
      break;
    }
  }
  return clause_evaluation_result;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateSelectStatementWithoutClauses() {
  std::shared_ptr<Result> evaluation_result = std::make_shared<Result>(ResultHeader{}, ResultTable{});

  for (const auto& kSynonym : synonym_tuple_) {
    if (evaluation_result->header_.count(kSynonym) == 0) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(kSynonym, pkb_, declaration_map_);
      evaluation_result->JoinResult(initial_result);
    }
  }

  return evaluation_result;
}

std::unordered_set<string> PqlEvaluator::GetFinalEvaluationResult(std::shared_ptr<Result>& clause_evaluation_result) {
  if (synonym_tuple_.empty()) {
    return clause_evaluation_result->ProjectResultForBoolean();
  }


  // only add the remaining selected synonym values into table if it is not already present in the header
  auto &header = clause_evaluation_result->header_;
  for (const auto& kSynonym : synonym_tuple_) {
    if (header.count(kSynonym) == 0) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(kSynonym, pkb_, declaration_map_);
      clause_evaluation_result->JoinResult(initial_result);
    }
  }

  std::unordered_set<std::string> results;
  results = clause_evaluation_result->ProjectResult(synonym_tuple_);
  return results;
}
