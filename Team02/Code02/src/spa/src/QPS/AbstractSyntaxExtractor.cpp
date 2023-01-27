#pragma once
#include "StringUtil.h"
#include <unordered_map>
#include "AbstractSyntaxExtractor.h"
#include "QPS/PqlException/SemanticErrorException.h"

AbstractSyntaxExtractor::AbstractSyntaxExtractor() = default;

/*
 * Extracts the first design entity in a string.
 */
std::string AbstractSyntaxExtractor::ExtractDesignEntity(const std::string& declaration) {
  std::string temp;
  for (char c : declaration) {
    temp.push_back(c);
    if (LexicalRuleValidator::IsDesignEntity(temp)) {
      break;
    }
  }
  return temp;
}

/*
 * Extracts the synonym as a key and the corresponding design entity as the value in an unordered map for further validation.
 */
std::unordered_map<std::string, std::string> AbstractSyntaxExtractor::ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations) {
  std::unordered_map<std::string, std::string> synonym_to_design_entity_map;
  std::string design_entity;

  for (const std::string &kDeclaration : declarations) {
    design_entity = ExtractDesignEntity(kDeclaration);
    std::string synonym_substring = kDeclaration.substr( design_entity.length());
    std::vector<std::string> synonym_list = string_util::SplitStringByDelimiter(synonym_substring, ",");
    for (const std::string &kSynonym : synonym_list) {
      if (synonym_to_design_entity_map.find(kSynonym) != synonym_to_design_entity_map.end()) {
        throw SemanticErrorException();
      }
      synonym_to_design_entity_map.insert({kSynonym, design_entity});
    }
  }
  return synonym_to_design_entity_map;
}
