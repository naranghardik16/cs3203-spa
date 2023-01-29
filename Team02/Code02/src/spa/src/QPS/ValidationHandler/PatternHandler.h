#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "..\PqlException\SyntaxErrorException.h"
#include "..\PqlException\SemanticErrorException.h"

class PatternHandler : public Handler {
 public:
  void Handle(Map &declaration, Map &clause) override;
};
