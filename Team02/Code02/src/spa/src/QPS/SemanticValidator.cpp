#include "SemanticValidator.h"

SemanticValidator::SemanticValidator() {
  has_semantic_error_ = false;
}

void SemanticValidator::ValidateSelectSemantics(SelectedSynonymTuple &synonym_vector) {
  if (has_semantic_error_) {
    return;
  }

  for (auto &syn : synonym_vector) {
    //if is synonym check if declared
    if (QueryUtil::IsSynonym(syn) && declaration_.find(syn) == declaration_.end()) {
      has_semantic_error_ = true;
      break;
    }

    //check attrRef, if synonym declared
    std::vector<std::string> token_lst = QueryUtil::SplitAttrRef(syn);
    auto it = declaration_.find(token_lst[0]);
    if (it == declaration_.end()) {
      has_semantic_error_ = true;
      break;
    }

    //check attrRef, if attr name is valid for the design entity
    auto attr_name = pql_constants::kEntityToAttrName.at(it->second);
    if (attr_name.find(token_lst[1]) == attr_name.end()) {
      has_semantic_error_ = true;
      break;
    }
  }
}

void SemanticValidator::ValidateSuchThatClauseSemantic(std::shared_ptr<ClauseSyntax> clause) {
  if (has_semantic_error_) {
    return;
  }

  try {
    std::shared_ptr<SuchThatBaseHandler> handler_1 = std::make_shared<SuchThatBaseHandler>();
    std::shared_ptr<StmtToStmtHandler> handler_2 = std::make_shared<StmtToStmtHandler>();
    std::shared_ptr<StmtProcToVarHandler> handler_3 = std::make_shared<StmtProcToVarHandler>();

    handler_1->SetNext(handler_2)->SetNext(handler_3);

    handler_1->HandleSemantic(clause, declaration_);
  } catch (const SemanticErrorException& e) {
    has_semantic_error_ = true;
  }
}

void SemanticValidator::ValidatePatternClauseSemantic(std::shared_ptr<ClauseSyntax> clause) {
  if (has_semantic_error_) {
    return;
  }

  try {
    std::shared_ptr<PatternHandler> handler = std::make_shared<PatternHandler>();

    handler->HandleSemantic(clause, declaration_);
  } catch (const SemanticErrorException& e) {
    has_semantic_error_ = true;
  }
}
