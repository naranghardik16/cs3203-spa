#pragma once
#include "QPS/QueryUtil.h"
#include "PqlEvaluator.h"
#include <stdexcept>

std::unordered_set<std::string> PqlEvaluator::Evaluate() {
  std::unordered_set<std::string> results;
  try {
    if (syntax_pair_list_->empty()) {
      results = EvaluateTrivialSelectStatement();
    }
    return results;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
  }
}

std::unordered_set<std::string> PqlEvaluator::EvaluateTrivialSelectStatement() {
  if (QueryUtil::IsVariableSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetVariables();
  } else if (QueryUtil::IsConstantSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetConstants();
  } else if (QueryUtil::IsAssignSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetAssignStatements();
  } else if (QueryUtil::IsIfSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetIfStatements();
  } else if (QueryUtil::IsStatementSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetStatements();
  } else if (QueryUtil::IsWhileSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetWhileStatements();
  } else if (QueryUtil::IsPrintSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetPrintStatements();
  } else if (QueryUtil::IsReadSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetReadStatements();
  } else if (QueryUtil::IsCallSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetCallStatements();
  } else if (QueryUtil::IsProcedureSynonym(*declaration_map_, *synonym_)) {
    return pkb_->GetProcedures();
  } else {
    throw std::invalid_argument("The synonym is not validated correctly as the synonym type cannot be identified");
  }
}