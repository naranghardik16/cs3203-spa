#pragma once
#include <iostream>
#include <utility>
#include <memory>
#include "General/LexicalRuleValidator.h"
#include "Tokenizer.h"
#include "QpsValidator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "QPSTypeDefs.h"

class QueryParser {
 public:
  ParserOutput ParseQuery(std::string query);
};

