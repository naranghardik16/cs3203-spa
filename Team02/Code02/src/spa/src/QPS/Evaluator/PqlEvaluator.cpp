#include "PqlEvaluator.h"

PqlEvaluator::PqlEvaluator(const std::shared_ptr<Query>& parser_output, std::shared_ptr<PkbReadFacade> pkb) {
  declaration_map_ = parser_output->GetDeclarationMap();
  synonym_tuple_ = parser_output->GetSynonymTuple();
  AdjustTrivialAttrRefs();
  syntax_list_ = parser_output->GetClauseSyntaxPtrList();
  is_return_empty_set_ = false;
  pkb_ = std::move(pkb);
  Optimizer opt;
  groups_ = opt.GetClauseGroups(syntax_list_);
}

void PqlEvaluator::AdjustTrivialAttrRefs() {
  //! remove trivial attr name e.g. r.stmt# is same as r
  for (int i = 0; i < synonym_tuple_.size(); ++i) {
    synonym_tuple_.at(i) = QueryUtil::AdjustSynonymWithTrivialAttrRefValue(synonym_tuple_[i], declaration_map_);
  }
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  if (!groups_.empty() && groups_[0]->GetSize() == 0) {
    EvaluateBooleanConstraints();
    groups_.erase(groups_.begin());
  }

  if (synonym_tuple_.empty()) {
    return EvaluateBooleanQuery();
  }

  if (is_return_empty_set_) {
    return {};
  }

  if (groups_.empty()) {
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

  if (is_return_empty_set_) {
    return {"FALSE"};
  }

  if (groups_.empty()) {
    return {"TRUE"};
  }

  auto clause_evaluation_result = GetClauseEvaluationResult();
  if (is_return_empty_set_) {
    return {"FALSE"};
  }
  return {"TRUE"};
}

void PqlEvaluator::EvaluateBooleanConstraints() {
  ClauseSyntaxPtrList clause_list = groups_[0]->GetClauseList();

  for (auto iter = clause_list.begin(); iter != clause_list.end(); ++iter) {
    auto clause = *iter;

    auto evaluator = clause->CreateClauseEvaluator(declaration_map_);
    auto is_clause_true = evaluator->EvaluateBooleanConstraint(pkb_);
    if (!is_clause_true) {
      is_return_empty_set_ = true;
      break;
    }
  }
}

std::vector<std::shared_ptr<Result>> PqlEvaluator::GetClauseEvaluationResult() {
  std::vector<std::shared_ptr<Result>> results;

  for (auto &group : groups_) {
    std::shared_ptr<Result> clause_evaluation_result = std::make_shared<Result>(ResultHeader{}, ResultTable{});
    ClauseSyntaxPtrList clause_list = group->GetClauseList();
    for (const auto& kClause : clause_list) {
      auto evaluator = kClause->CreateClauseEvaluator(declaration_map_);
      std::shared_ptr<Result> intermediate_result = evaluator->EvaluateClause(pkb_);

      // get intersection
      clause_evaluation_result->JoinResult(intermediate_result);

      // Whenever results become empty stop and return empty set
      if (clause_evaluation_result->GetTable().empty()) {
        is_return_empty_set_ = true;
        return {};
      }
    }
    if (group->HasSelectedSynonym(synonym_tuple_)) {
      results.push_back(clause_evaluation_result);
    }
  }

  return results;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateSelectStatementWithoutClauses() {
  std::shared_ptr<Result> evaluation_result = std::make_shared<Result>(ResultHeader{}, ResultTable{});

  for (const auto& kSynonym : synonym_tuple_) {
    if (evaluation_result->GetHeader().count(kSynonym) == 0) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(kSynonym, pkb_, declaration_map_);
      evaluation_result->JoinResult(initial_result);
    }
  }

  return evaluation_result;
}

std::unordered_set<string> PqlEvaluator::GetFinalEvaluationResult(
    std::vector<std::shared_ptr<Result>>& clause_evaluation_results
    ) {
  std::shared_ptr<Result> crossed_result = std::make_shared<Result>(ResultHeader{}, ResultTable{});
  for (auto &result : clause_evaluation_results) {
    crossed_result->JoinResult(result);
  }
  // only add the remaining selected synonym values into table if it is not already present in the header
  auto &header = crossed_result->GetHeader();
  for (const auto& kSynonym : synonym_tuple_) {
    if (header.count(kSynonym) == 0) {
      auto initial_result = DesignEntityGetter::EvaluateBasicSelect(kSynonym, pkb_, declaration_map_);
      crossed_result->JoinResult(initial_result);
    }
  }

  std::unordered_set<std::string> results;
  results = crossed_result->ProjectResult(synonym_tuple_);
  return results;
}
