#pragma once

#include "Handler.h"

/*
 * Validate stmt/proc and variable relationship (Uses, Modifies).
 */
class StmtProcToVarHandler : public Handler{
 public:
  void HandleSyntax(std::shared_ptr<ClauseSyntax> clause) override;
  void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) override;
  bool CanHandler(std::string &rel_ref);
};
