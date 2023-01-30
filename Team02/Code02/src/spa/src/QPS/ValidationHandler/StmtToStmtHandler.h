#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

/*
 * Validate stmt and stmt relationship (Follows, Follows*, Parent, Parent*).
 */
class StmtToStmtHandler : public Handler {
 public:
  void Handle(Map &declaration, Map &clause) override;
};
