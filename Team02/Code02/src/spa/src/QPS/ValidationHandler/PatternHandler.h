#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

class PatternHandler : public Handler {
 public:
  void Handle(Map &declaration, Map &clause) override;
};
