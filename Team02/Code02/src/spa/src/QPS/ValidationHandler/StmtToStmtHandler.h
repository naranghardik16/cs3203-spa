#pragma once

#include "Handler.h"

/*
 * Validate stmt and stmt relationship (Follows, Follows*, Parent, Parent*).
 */
class StmtToStmtHandler : public Handler {
 public:
  void HandleSyntax(ClauseSyntax *clause) override;
  void HandleSemantic(ClauseSyntax *clause, Map &declaration) override;
  bool CanHandler(std::string &rel_ref);
};
