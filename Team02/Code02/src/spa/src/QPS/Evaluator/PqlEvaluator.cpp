#pragma once
#include "QPS/Util/QueryUtil.h"
#include "PqlEvaluator.h"
#include <stdexcept>

PqlEvaluator::PqlEvaluator(std::shared_ptr<Query> parser_output, std::shared_ptr<PKB> pkb) {
  synonym_ = parser_output->GetSynonym();
  declaration_map_ = parser_output->GetDeclarationMap();
  syntax_pair_list_ = parser_output->GetClauseSyntaxPtrList();
  pkb_ptr_ = pkb;
}

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  std::unordered_set<std::string> results;
  try {
    if (syntax_pair_list_.empty()) {
      results = EvaluateTrivialSelectStatement();
    }
    return results;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
  }
}

std::unordered_set<std::string> PqlEvaluator::EvaluateTrivialSelectStatement() {
  if (QueryUtil::IsVariableSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetVariables();
  } else if (QueryUtil::IsConstantSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetConstants();
  } else if (QueryUtil::IsAssignSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetAssignStatements();
  } else if (QueryUtil::IsIfSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetIfStatements();
  } else if (QueryUtil::IsStatementSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetStatements();
  } else if (QueryUtil::IsWhileSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetWhileStatements();
  } else if (QueryUtil::IsPrintSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetPrintStatements();
  } else if (QueryUtil::IsReadSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetReadStatements();
  } else if (QueryUtil::IsCallSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetCallStatements();
  } else if (QueryUtil::IsProcedureSynonym(declaration_map_, synonym_)) {
    return pkb_ptr_->GetProcedures();
  } else {
    throw std::invalid_argument("The synonym is not validated correctly as the synonym type cannot be identified");
  }
}