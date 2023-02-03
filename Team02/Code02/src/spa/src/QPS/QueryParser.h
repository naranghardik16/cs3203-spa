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

class QueryParser {
 public:
  std::shared_ptr<Query> ParseQuery(std::string query);
};

