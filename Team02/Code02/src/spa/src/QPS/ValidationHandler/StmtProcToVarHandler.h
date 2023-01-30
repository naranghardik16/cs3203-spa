#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

/*
 * Validate stmt/proc and variable relationship (Uses, Modifies).
 */
class StmtProcToVarHandler : public Handler{
 public:
  void Handle(Map &declaration, Map &clause) override;
};
