#pragma once

#include <iostream>
#include <utility>
#include <memory>
#include "General/LexicalRuleValidator.h"
#include "QpsTokenizer.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "Query.h"

/**
 * This is a facade to handle the parsing of queries by tokenizer and validators
 */
class QueryParser {
 public:
  std::shared_ptr<Query> ParseQuery(std::string query);
};
