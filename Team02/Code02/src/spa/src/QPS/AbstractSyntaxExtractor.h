#pragma once
#include <iostream>
#include <unordered_map>
#include "General/LexicalRuleValidator.h"

class AbstractSyntaxExtractor {
 public:
  AbstractSyntaxExtractor();

  static std::string ExtractDesignEntity(const std::string& declaration);

  static std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations);

  static std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromClause(const std::string& clause,const std::string& clause_start_indicator);

};
