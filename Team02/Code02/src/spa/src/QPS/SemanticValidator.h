#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/ValidationHandler/WithHandler.h"
#include "QPS/ValidationHandler/CallsHandler.h"

class SemanticValidator {
 public:
  SemanticValidator();
  void ValidateSelectSemantics(SelectedSynonymTuple &synonym_vector);
  void ValidateSuchThatClauseSemantic(std::shared_ptr<ClauseSyntax> clause);
  void ValidatePatternClauseSemantic(std::shared_ptr<ClauseSyntax> clause);
  void ValidateWithClauseSemantic(std::shared_ptr<ClauseSyntax> clause);
  bool HasSemanticError() const;
  void SetHasSemanticError(bool has_semantic_error);
  void SetDeclaration(const Map &declaration);

 private:
  Map declaration_;
  bool has_semantic_error_;
};
