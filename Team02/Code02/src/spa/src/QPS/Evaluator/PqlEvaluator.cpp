#pragma once
#include "QPS/Util/QueryUtil.h"
#include "PqlEvaluator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include <stdexcept>
#include <utility>

PqlEvaluator::PqlEvaluator(const std::shared_ptr<Query>& parser_output, std::shared_ptr<PkbReadFacade> pkb) {
  synonym_ = parser_output->GetSynonym();
  declaration_map_ = parser_output->GetDeclarationMap();
  syntax_pair_list_ = parser_output->GetClauseSyntaxPtrList();
  pkb_ = std::move(pkb);
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  std::shared_ptr<Result> evaluation_result = EvaluateBasicSelectStatement();

  //!Evaluate and remove all boolean constraints first
  for (int i=0; i<syntax_pair_list_.size();i++) {
    auto clause = syntax_pair_list_[i];
    auto is_bool_constraint = clause->IsBooleanClause(declaration_map_);

    if (is_bool_constraint) {
      auto evaluator = clause->CreateClauseEvaluator(synonym_, declaration_map_);
      auto is_clause_true = evaluator->EvaluateBooleanConstraint(pkb_);
      if (!is_clause_true) {
        return {};
      }
      syntax_pair_list_.erase(syntax_pair_list_.begin()+i);
    }
  }

  //Evaluate the remaining constraints and use intersection of result classes to resolve constraints
  for (const auto &kClause : syntax_pair_list_) {
    auto evaluator = kClause->CreateClauseEvaluator(synonym_, declaration_map_);
    std::shared_ptr<Result> intermediate_result = evaluator->EvaluateClause(pkb_);

    //get intersection
    evaluation_result->JoinResult(intermediate_result);

    //Whenever results become empty stop and return empty set
    if (evaluation_result->table_.empty()) {
      return {};
    }
  }

  std::unordered_set<std::string> results = evaluation_result->ProjectResult(synonym_);

  return results;
}

std::shared_ptr<Result> PqlEvaluator::EvaluateBasicSelectStatement() {
  ResultHeader header;
  header.push_back(synonym_);
  ResultTable table;
  if (QueryUtil::IsVariableSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetVariables());
  } else if (QueryUtil::IsConstantSynonym(declaration_map_, synonym_)) {
    table =  QueryUtil::ConvertSetToResultTableFormat(pkb_->GetConstants());
  } else if (QueryUtil::IsAssignSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetAssignStatements());
  } else if (QueryUtil::IsIfSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetIfStatements());
  } else if (QueryUtil::IsStatementSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetStatements());
  } else if (QueryUtil::IsWhileSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetWhileStatements());
  } else if (QueryUtil::IsPrintSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetPrintStatements());
  } else if (QueryUtil::IsReadSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetReadStatements());
  } else if (QueryUtil::IsCallSynonym(declaration_map_, synonym_)) {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetCallStatements());
  } else  {
    table = QueryUtil::ConvertSetToResultTableFormat(pkb_->GetProcedures());
  }
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
