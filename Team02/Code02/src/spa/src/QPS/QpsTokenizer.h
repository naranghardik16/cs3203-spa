#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <unordered_map>
#include "General/StringUtil.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/ClauseSyntaxValidator.h"
#include "QPS/ClauseSemanticValidator.h"

class QpsTokenizer {

 public:
  std::shared_ptr<ClauseSyntaxValidator> syntax_validator_;
  std::shared_ptr<ClauseSemanticValidator> semantic_validator_;

  QpsTokenizer();
  QueryStatementPair SplitQuery(const std::string& query_extra_whitespace_removed);

  std::string ParseSynonym(const std::string& clause);

  size_t FindStartOfSubClauseIndex(const std::string& s, const std::regex& rgx);

  std::vector<size_t> GetIndexListOfClauses(const std::string& statement);

  std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations);

  SyntaxPair ExtractAbstractSyntaxFromClause(const std::string& clause,const std::string& clause_start_indicator);

  std::vector<std::shared_ptr<ClauseSyntax>> ParseSubClauses(const std::string &statement);

};
