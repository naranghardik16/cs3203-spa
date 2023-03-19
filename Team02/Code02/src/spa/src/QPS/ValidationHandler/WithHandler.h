#pragma once

#include "Handler.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

class WithHandler : public Handler {
 public:
  void HandleSyntax(std::shared_ptr<ClauseSyntax> clause) override;
  void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) override;

  //helper
  static std::string CheckAttrRef(std::string &ref, Map &declaration);
  static std::string GetAttrType(std::string &ref);
};
