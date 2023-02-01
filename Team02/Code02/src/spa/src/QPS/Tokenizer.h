#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <unordered_map>
#include "General/StringUtil.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Clause/ClauseSyntax.h"

typedef std::pair<std::string, std::pair<std::string, std::string>> SyntaxPair;
typedef std::pair<std::string, std::string> ParameterPair;
typedef std::pair<std::vector<std::string>, std::string> QueryStatementPair;

class Tokenizer {

 public:
  QueryStatementPair SplitQuery(const std::string& query_extra_whitespace_removed);

  std::string ParseSynonym(const std::string& clause);

  size_t FindStartOfSubClauseIndex(const std::string& s, const std::regex& rgx);

  std::vector<size_t> GetIndexListOfClauses(const std::string& statement);

  std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations);

  SyntaxPair ExtractAbstractSyntaxFromClause(const std::string& clause,const std::string& clause_start_indicator);

  std::vector<std::shared_ptr<ClauseSyntax>> ParseSubClauses(const std::string &statement);

};
