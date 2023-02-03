#pragma once

#include <memory>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "QPS/Clause/PatternClauseSyntax.h"

class Visitor {
 public:
  virtual void VisitSuchThatClause(SuchThatClauseSyntax *clause) const = 0;
  virtual void VisitPatternClause(PatternClauseSyntax *clause) const = 0;
};
