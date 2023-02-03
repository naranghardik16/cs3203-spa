#pragma once

#include "Handler.h"
#include "General/LexicalRuleValidator.h"

class PatternHandler : public Handler {
 public:
  void HandleSyntax(ClauseSyntax *clause) override;
  void HandleSemantic(ClauseSyntax *clause, Map &declaration) override;
};
