#pragma once

#include <memory>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPSTypeDefs.h"

class ClauseSemanticValidator {
 public:
  Map declaration_;
  bool has_semantic_error_;
  ClauseSemanticValidator();
  void ValidateSuchThatClauseSemantic(std::shared_ptr<ClauseSyntax> clause);
  void ValidatePatternClauseSemantic(std::shared_ptr<ClauseSyntax> clause);
};
