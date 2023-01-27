#pragma once
#include <iostream>
#include "QPS/LexicalRuleValidator.h"

class AbstractSyntaxExtractor {
 public:
  AbstractSyntaxExtractor();

  static std::string ExtractDesignEntity(const std::string& declaration);

  static std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations);
};
