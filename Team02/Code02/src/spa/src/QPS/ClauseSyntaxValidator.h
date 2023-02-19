#pragma once

#include <memory>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPS/Clause/ClauseSyntax.h"

class ClauseSyntaxValidator{
 public:
  void ValidateSuchThatClauseSyntax(std::shared_ptr<ClauseSyntax> clause);
  void ValidatePatternClauseSyntax(std::shared_ptr<ClauseSyntax> clause);
};
