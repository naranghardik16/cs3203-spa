#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <unordered_map>
#include "General/StringUtil.h"
#include "General/LexicalRuleValidator.h"

class Tokenizer {

 public:
  std::unordered_map<std::string, std::vector<std::string>> AddDeclarationsAndStatementsIntoMap(const std::string& query,
                                                                                                           std::unordered_map<std::string, std::vector<std::string>>& map);

  std::unordered_map<std::string, std::vector<std::string>> AddSelectSubclausesIntoMap(const std::string& clause, std::unordered_map<std::string, std::vector<std::string>>& map);


  std::unordered_map<std::string, std::vector<std::string>> AddSubclausesIntoMap(const std::string& clause,
                                                                                        std::unordered_map<std::string, std::vector<std::string>>& map);

  std::unordered_map<std::string, std::vector<std::string>> AddSynonymIntoMap(const std::string& clause,
                                                                                         std::unordered_map<std::string, std::vector<std::string>>& map);

  std::unordered_map<std::string, std::vector<std::string>> TokenizeQuery(const std::string& query);

  std::vector<size_t> GetIndexListOfClauses(const std::string& statement);

  size_t FindStartOfSubClauseIndex(const std::string& s, const std::regex& rgx);
};
