#pragma once
#include <iostream>
#include <utility>
#include "LexicalRuleValidator.h"
#include "Tokenizer.h"

// need to take note of wrapping pointers
class QueryParser {
 private:
  std::shared_ptr<LexicalRuleValidator> lexical_rule_validator_ = std::shared_ptr<LexicalRuleValidator>();
  std::shared_ptr<Tokenizer> tokenizer_ = std::shared_ptr<Tokenizer>();
  
 public:
  void ParseQuery(std::string query) {
    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    subclauses_map = tokenizer_->TokenizeQuery(std::move(query));
    std::vector<std::string> declaration_statements = subclauses_map["Declaration"];
    std::vector<std::string> select_statements = subclauses_map["Select"];
    std::vector<std::string> synonyms = subclauses_map["Synonym"];
    std::vector<std::string> such_that_statements = subclauses_map["Such That"];
    std::vector<std::string> pattern_statements = subclauses_map["Pattern"];
  }


};

