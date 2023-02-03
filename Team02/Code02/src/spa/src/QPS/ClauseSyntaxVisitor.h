#pragma once

#include "Visitor.h"

class ClauseSyntaxVisitor : public Visitor{
 public:
  void VisitSuchThatClause(SuchThatClauseSyntax *clause) const override;
  void VisitPatternClause(PatternClauseSyntax *clause) const override;
};
