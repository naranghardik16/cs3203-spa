//#pragma once
#include "QueryParser.h"
#include "PQLConstants.h"

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> QueryParser::ParseQuery(std::string query) {
  std::shared_ptr<Tokenizer> tk = std::make_shared<Tokenizer>();
  std::shared_ptr<AbstractSyntaxExtractor> ase = std::make_shared<AbstractSyntaxExtractor>();
  try {
    //Tokenize by splitting the query into its subclauses
    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    subclauses_map = tk->TokenizeQuery(std::move(query));
    std::vector<std::string> declaration_statements = subclauses_map[pql_constants::kDeclarationKey];
    std::vector<std::string> select_statements = subclauses_map[pql_constants::kSelectKey];
    std::vector<std::string> synonyms = subclauses_map[pql_constants::kSynonymKey];

    std::string such_that_statement;
    if (subclauses_map[pql_constants::kSuchThatKey].empty()) {
      such_that_statement = "";
    } else {
      such_that_statement = subclauses_map[pql_constants::kSuchThatKey][0];
    }

    std::string pattern_statement;
    if (subclauses_map[pql_constants::kPatternKey].empty()) {
      pattern_statement = "";
    } else {
      pattern_statement = subclauses_map[pql_constants::kSuchThatKey][0];
    }

    //Extract the abstract syntax from the query. If the clause is empty then an empty map is returned.
    auto declaration_map = ase->ExtractAbstractSyntaxFromDeclarations(declaration_statements);
    auto such_that_map =
        ase->ExtractAbstractSyntaxFromClause(such_that_statement, pql_constants::kSuchThatStartIndicator);
    auto pattern_map =
        ase->ExtractAbstractSyntaxFromClause(pattern_statement, pql_constants::kPatternStartIndicator);

    //Validate the query
    QpsValidator::Validate(declaration_map, such_that_map, pattern_map);

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> final_map;
    return final_map;
  } catch (const SyntaxErrorException& e) {
  } catch (const SemanticErrorException& e) {
  }
}


