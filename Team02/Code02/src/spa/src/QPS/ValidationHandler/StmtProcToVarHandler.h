#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "..\PqlException\SemanticErrorException.h"
#include "..\PqlException\SyntaxErrorException.h"

/*
 * Validate stmt/proc and variable relationship (Uses, Modifies).
 */
class StmtProcToVarHandler : public Handler{
 public:
  void Handle(Map &declaration, Map &clause) override;
};
