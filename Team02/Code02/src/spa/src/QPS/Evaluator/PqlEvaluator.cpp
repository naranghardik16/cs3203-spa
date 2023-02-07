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
  Map map_test = declaration_map_;

  std::unordered_set<std::string> results;
  if (syntax_pair_list_.empty()) {
    results = EvaluateTrivialSelectStatement();
    return results;
  }

  std::vector<std::vector<std::string>> evaluation_result;
  for (const auto &kClause : syntax_pair_list_) {
    auto evaluator = kClause->CreateClauseEvaluator(synonym_, declaration_map_);
    auto evaluation_result = evaluator->EvaluateClause(pkb_);
    //store result into table
    //get intersection if needed
  }

  results = QueryUtil::ConvertToSet(evaluation_result);

  return results;
}


//TODO change to vector<vector<std::string>>
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
