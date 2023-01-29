#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <unordered_map>
#include "General/StringUtil.h"
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

  static std::vector<size_t> GetIndexListOfClauses(const std::string& statement);

  static size_t FindStartOfSubClauseIndex(std::string s, std::regex rgx);
};
