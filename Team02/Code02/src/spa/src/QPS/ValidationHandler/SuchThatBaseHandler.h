#pragma once

#include "Handler.h"

class SuchThatBaseHandler : public Handler {
 public:
  /*
   * First syntax handler for such that clause:
   * - Check if relRef is valid
   */
  void HandleSyntax(ClauseSyntax *clause) override;

  /*
   * First semantic handler for such that clause:
   * - Check if synonyms used are declared
   */
  void HandleSemantic(ClauseSyntax *clause, Map &declaration) override;
};
