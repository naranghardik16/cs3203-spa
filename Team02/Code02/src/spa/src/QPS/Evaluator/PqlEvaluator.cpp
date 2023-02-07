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

bool PqlEvaluator::IsBooleanConstraint(const SyntaxPair& pair) {
  auto first_arg = pair.second.first;
  auto second_arg = pair.second.second;
  bool is_first_arg_a_synonym = declaration_map_.count(first_arg);
  bool is_second_arg_a_synonym = declaration_map_.count(second_arg);
  bool has_synonym = (is_first_arg_a_synonym) || is_second_arg_a_synonym;
  return !has_synonym;
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  Map map_test = declaration_map_;

  std::unordered_set<std::string> results;
  if (syntax_pair_list_.empty()) {
    results = EvaluateTrivialSelectStatement();
    return results;
  }

  //!Evaluate and remove all boolean constraints first
  for (int i=0; i<syntax_pair_list_.size();i++) {
    auto clause = syntax_pair_list_[i];
    auto is_bool_constraint = IsBooleanConstraint(clause->GetSyntaxPair());

    if (is_bool_constraint) {
      auto evaluator = clause->CreateClauseEvaluator(synonym_, declaration_map_);
      auto bool_output = evaluator->EvaluateBooleanConstraint(pkb_);
      if (bool_output == false) {
        std::unordered_set<std::string> empty_set;
        return empty_set;
      }
      syntax_pair_list_.erase(syntax_pair_list_.begin()+i);
    }
  }

  std::shared_ptr<Result> evaluation_result;
  for (const auto &kClause : syntax_pair_list_) {
    auto evaluator = kClause->CreateClauseEvaluator(synonym_, declaration_map_);
    evaluation_result = evaluator->EvaluateClause(pkb_);
    //store result into table
    //get intersection if needed
  }

  ResultTable result_table = evaluation_result->GetResultTable();
  results = QueryUtil::ConvertToSet(result_table);

  return results;
}

//TODO Should return Result
std::unordered_set<std::string> PqlEvaluator::EvaluateTrivialSelectStatement() {
  if (QueryUtil::IsVariableSynonym(declaration_map_, synonym_)) {
    return pkb_->GetVariables();
  } else if (QueryUtil::IsConstantSynonym(declaration_map_, synonym_)) {
    return pkb_->GetConstants();
  } else if (QueryUtil::IsAssignSynonym(declaration_map_, synonym_)) {
    return pkb_->GetAssignStatements();
  } else if (QueryUtil::IsIfSynonym(declaration_map_, synonym_)) {
    return pkb_->GetIfStatements();
  } else if (QueryUtil::IsStatementSynonym(declaration_map_, synonym_)) {
    return pkb_->GetStatements();
  } else if (QueryUtil::IsWhileSynonym(declaration_map_, synonym_)) {
    return pkb_->GetWhileStatements();
  } else if (QueryUtil::IsPrintSynonym(declaration_map_, synonym_)) {
    return pkb_->GetPrintStatements();
  } else if (QueryUtil::IsReadSynonym(declaration_map_, synonym_)) {
    return pkb_->GetReadStatements();
  } else if (QueryUtil::IsCallSynonym(declaration_map_, synonym_)) {
    return pkb_->GetCallStatements();
  } else if (QueryUtil::IsProcedureSynonym(declaration_map_, synonym_)) {
    return pkb_->GetProcedures();
  } else {
    throw std::invalid_argument("The synonym is not validated correctly as the synonym type cannot be identified");
  }
}
