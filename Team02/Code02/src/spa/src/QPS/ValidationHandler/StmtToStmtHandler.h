#pragma once

#include "Handler.h"

/*
 * Validate stmt and stmt relationship (Follows, Follows*, Parent, Parent*).
 */
class StmtToStmtHandler : public Handler {
 public:
  void HandleSyntax(std::shared_ptr<ClauseSyntax> clause) override;
  void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) override;
  static bool CanHandler(std::string &rel_ref);
};
