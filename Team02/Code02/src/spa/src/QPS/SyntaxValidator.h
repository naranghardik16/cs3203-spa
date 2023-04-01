#pragma once

#include <memory>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/ValidationHandler/WithHandler.h"
#include "QPS/ValidationHandler/CallsHandler.h"

class SyntaxValidator{
 public:
  void ValidateSelectSyntax(SelectedSynonymTuple &synonym_vector);
  void ValidateSuchThatClauseSyntax(std::shared_ptr<ClauseSyntax> clause);
  void ValidatePatternClauseSyntax(std::shared_ptr<ClauseSyntax> clause);
  void ValidateWithClauseSyntax(std::shared_ptr<ClauseSyntax> clause);
};
