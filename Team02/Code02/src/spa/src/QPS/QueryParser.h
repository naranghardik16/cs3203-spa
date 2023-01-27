#pragma once
#include <iostream>
#include <utility>
#include "LexicalRuleValidator.h"
#include "AbstractSyntaxExtractor.h"
#include "Tokenizer.h"
#include "PqlException/SyntaxErrorException.h"
#include "PqlException/SemanticErrorException.h"

class QueryParser {
 public:
  static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> QueryParser::ParseQuery(std::string query);
};

