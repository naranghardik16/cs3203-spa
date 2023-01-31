#pragma once
#include "General/StringUtil.h"
#include <unordered_map>
#include "AbstractSyntaxExtractor.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "QPS/PQLConstants.h"

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
    design_entity = string_util::GetFirstWord(kDeclaration);
    if (!LexicalRuleValidator::IsDesignEntity(design_entity)) {
      throw SyntaxErrorException();
    }
    std::string synonym_substring = string_util::GetClauseAfterKeyword(kDeclaration, design_entity);
    std::vector<std::string> synonym_list = string_util::SplitStringByDelimiter(synonym_substring, ",");
    for (const std::string &kSynonym : synonym_list) {
      if (synonym_to_design_entity_map.find(kSynonym) != synonym_to_design_entity_map.end()) {
        throw SemanticErrorException(); //repeated synonyms
      }
      if (!LexicalRuleValidator::IsSynonym(kSynonym)) {
        throw SyntaxErrorException();
      }
      synonym_to_design_entity_map.insert({kSynonym, design_entity});

    }
  }


  return synonym_to_design_entity_map;
}

/*
 * Extracts the entity (e.g. the relationship reference or the syn-assign), parameters in the relationship reference
 * from a such that clause or pattern clause.
 * Throws SyntaxErrorException if the concrete syntax in a such that clause cannot be found.
 * Returns an empty map if the clause is empty because it is optional to have a such that clause.
 */
std::unordered_map<std::string, std::string> AbstractSyntaxExtractor::ExtractAbstractSyntaxFromClause(const std::string& clause,
                                                                                                      const std::string& clause_start_indicator) {
  std::unordered_map<std::string, std::string> map;

  if (clause.empty()) {
    return map;
  }

  size_t start_of_rel_ref_index = clause.find(clause_start_indicator) + clause_start_indicator.length();
  size_t opening_bracket_index = clause.find(pql_constants::kOpeningBracket);
  size_t comma_index = clause.find(pql_constants::kComma);
  size_t closing_bracket_index = clause.find_last_of(pql_constants::kClosingBracket);

  if ((start_of_rel_ref_index == std::string::npos) || (opening_bracket_index == std::string::npos) ||
      (comma_index == std::string::npos) || (closing_bracket_index == std::string::npos)) {
    throw SyntaxErrorException();
  }

  std::string relationship = string_util::Trim(clause.substr(start_of_rel_ref_index,
                                                                       opening_bracket_index - start_of_rel_ref_index));
  std::string first_parameter = string_util::Trim(clause.substr(opening_bracket_index+1,

                                                                          comma_index - (opening_bracket_index+1)));
  std::string second_parameter = string_util::Trim(clause.substr(comma_index+1,
                                                                 closing_bracket_index-(comma_index+1)));

  if (first_parameter.empty() || relationship.empty() || second_parameter.empty()) {
    throw SyntaxErrorException();
  }

  map.insert({pql_constants::kEntityKey, relationship});
  map.insert({pql_constants::kFirstParameterKey, first_parameter});
  map.insert({pql_constants::kSecondParameterKey, second_parameter});

  return map;
}


