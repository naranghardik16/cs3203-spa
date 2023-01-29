#pragma once
#include "QueryParser.h"

const std::string kSuchThatStartIndicator = "such that ";
const std::string kPatternStartIndicator = "pattern ";

const std::string kDeclarationKey = "Declarations";
const std::string kSelectKey = "Select";
const std::string kSynonymKey = "Synonym";
const std::string kSuchThatKey = "Such That";
const std::string kPatternKey = "Pattern";
const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";


std::unordered_map<std::string, std::unordered_map<std::string, std::string>> QueryParser::ParseQuery(std::string query) {
  try {
    //Tokenize by splitting the query into its subclauses
    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    subclauses_map = Tokenizer::TokenizeQuery(std::move(query));
    std::vector<std::string> declaration_statements = subclauses_map[kDeclarationKey];
    std::vector<std::string> select_statements = subclauses_map[kSelectKey];
    std::vector<std::string> synonyms = subclauses_map[kSynonymKey];

    std::string such_that_statement;
    if (subclauses_map[kSuchThatKey].empty()) {
      such_that_statement = "";
    } else {
      such_that_statement = subclauses_map[kSuchThatKey][0];
    }

    std::string pattern_statement;
    if (subclauses_map[kPatternKey].empty()) {
      pattern_statement = "";
    } else {
      pattern_statement = subclauses_map[kSuchThatKey][0];
    }

    //Extract the abstract syntax from the query. If the clause is empty then an empty map is returned.
    auto declaration_map = AbstractSyntaxExtractor::ExtractAbstractSyntaxFromDeclarations(declaration_statements);
    auto such_that_map =
        AbstractSyntaxExtractor::ExtractAbstractSyntaxFromClause(such_that_statement, kSuchThatStartIndicator);
    auto pattern_map =
        AbstractSyntaxExtractor::ExtractAbstractSyntaxFromClause(pattern_statement, kPatternStartIndicator);

    //Validate the query


    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> final_map;
    return final_map;
  } catch (const SyntaxErrorException& e) {
  } catch (const SemanticErrorException& e) {
  }
}


