#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>
#include "StringUtil.h"
#include "LexicalRuleValidator.h"

class Tokenizer {

 public:
  static std::unordered_map<std::string, std::vector<std::string>> AddDeclarationsAndStatementsIntoMap(std::string query,
                                                                                                           std::unordered_map<std::string, std::vector<std::string>>& map);

  static std::unordered_map<std::string, std::vector<std::string>> AddSelectSubclausesIntoMap(const std::string& clause, std::unordered_map<std::string, std::vector<std::string>>& map);


  static std::unordered_map<std::string, std::vector<std::string>> AddSubclausesIntoMap(const std::string& clause,
                                                                                        std::unordered_map<std::string, std::vector<std::string>>& map);

  static std::unordered_map<std::string, std::vector<std::string>> AddSynonymIntoMap(const std::string& clause,
                                                                                         std::unordered_map<std::string, std::vector<std::string>>& map);

  static std::unordered_map<std::string, std::vector<std::string>> TokenizeQuery(std::string query);

  static bool IsSuchThat(const std::string& clause);

  static bool IsPattern(const std::string& clause);

  static std::vector<size_t> GetIndexListOfClauses(const std::string& statement);
};
