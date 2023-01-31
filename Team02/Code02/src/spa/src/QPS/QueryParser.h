#pragma once
#include <iostream>
#include <utility>
#include <memory>
#include "General/LexicalRuleValidator.h"
#include "Tokenizer.h"
#include "QpsValidator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

typedef std::pair<std::string, std::pair<std::string, std::string>> SyntaxPair;
typedef std::string Synonym;
typedef std::string DesignEntity;
typedef std::unordered_map<Synonym, DesignEntity> DeclarationMap;
typedef std::pair<Synonym, std::pair<std::vector<std::shared_ptr<ClauseSyntax>>, DeclarationMap>> ParserOutput;

class QueryParser {
 public:
  ParserOutput ParseQuery(std::string query);
};

