#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "..\PqlException\SemanticErrorException.h"
#include "..\PqlException\SyntaxErrorException.h"

class FollowHandler : public Handler {
 public:
  void Handle(Map &declaration, Map &clause) override;
};
