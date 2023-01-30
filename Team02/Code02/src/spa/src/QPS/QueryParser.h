#pragma once
#include <iostream>
#include <utility>
#include "General/LexicalRuleValidator.h"
#include "AbstractSyntaxExtractor.h"
#include "Tokenizer.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

class QueryParser {
 public:
  static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ParseQuery(std::string query);
};

