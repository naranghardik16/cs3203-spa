#pragma once

#include "Handler.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/ExpressionSpecParser.h"

class PatternHandler : public Handler {
 public:
  void HandleSyntax(std::shared_ptr<ClauseSyntax> clause) override;
  void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) override;
};
