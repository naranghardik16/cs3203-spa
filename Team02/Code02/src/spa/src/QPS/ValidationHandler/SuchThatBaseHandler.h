#pragma once

#include "Handler.h"
#include <unordered_set>
#include "General/LexicalRuleValidator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

class SuchThatBaseHandler : public Handler {
 public:
  /*
   * First handler for such that clause, does two basic checks.
   * 1. Check if there is such that clause (i.e. clause_map.size() != 0)
   * 2. Check if relRef is valid
   * 3. Check if synonyms used is declared
   */
  void Handle(Map &declaration, Map &clause) override;
};
