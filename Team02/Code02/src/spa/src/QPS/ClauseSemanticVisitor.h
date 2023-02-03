#pragma once

#include "Visitor.h"
#include "QPSTypeDefs.h"

class ClauseSemanticVisitor : public Visitor{
 public:
  Map &declaration_;
  ClauseSemanticVisitor(Map &declaration);
  void VisitSuchThatClause(SuchThatClauseSyntax *clause) const override;
  void VisitPatternClause(PatternClauseSyntax *clause) const override;
};
