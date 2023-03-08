#pragma once

#include "Handler.h"

class AffectsHandler : public Handler {
 public:
  void HandleSyntax(std::shared_ptr<ClauseSyntax> clause) override;
  void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) override;
  static bool CanHandler(std::string &rel_ref);
};

