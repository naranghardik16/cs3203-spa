#include <iostream>

// Forward declarationsof classes if any

// List typedefs
//Tokenizer
typedef std::pair<std::vector<std::string>, std::string> QueryStatementPair;

//Validator
typedef std::unordered_map<std::string, std::string> Map;

//Parser
typedef std::pair<std::string, std::string> ParameterPair;
typedef std::pair<std::string, ParameterPair> SyntaxPair;
typedef std::string Synonym;
typedef std::string DesignEntity;
typedef std::unordered_map<Synonym, DesignEntity> DeclarationMap;
typedef std::pair<Synonym, std::pair<std::vector<std::shared_ptr<ClauseSyntax>>, DeclarationMap>> ParserOutput;
