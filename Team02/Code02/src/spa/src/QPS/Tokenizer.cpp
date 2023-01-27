#pragma once
#include "Tokenizer.h"
#include "StringUtil.h"
#include <utility>
#include "QPS/PqlException/SyntaxErrorException.h"

const std::string kDeclarationKey = "Declarations";
const std::string kSelectKey = "Select";
const std::string kSynonymKey = "Synonym";
const std::string kSuchThatKey = "Such That";
const std::string kPatternKey = "Pattern";

const std::string kSelectKeyword = "Select";
const std::string kSuchThatStartIndicator = "such that ";
const std::string kPatternStartIndicator = "pattern ";

/*
 * Splits the query into declarations and select statement then adds this values into a map.
 * Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::AddDeclarationsAndStatementsIntoMap(std::string query,
                                                                                std::unordered_map<std::string, std::vector<std::string>>& map) {
    std::string delimiter = ";";
    std::vector<std::string> declaration_statements;
    std::vector<std::string> select_statements;
    std::string declaration;

    size_t delimiter_index = query.find(delimiter);
    while (delimiter_index != std::string::npos) {
      declaration = string_util::Trim(query.substr(0, delimiter_index));
      declaration_statements.push_back(declaration);
      query.erase(0, delimiter_index + delimiter.length());
      delimiter_index = query.find(delimiter);
    }

    select_statements.push_back(string_util::Trim(query));

    map.insert({kDeclarationKey, declaration_statements});
    map.insert({kSelectKey, select_statements});
    return map;
}

/*
 * Parses for the synonym in the clause and adds the synonym into the map.
 * Throws an exception if there is no synonym found.
 */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::AddSynonymIntoMap(const std::string& clause,
                                                                                       std::unordered_map<std::string, std::vector<std::string>>& map) {
  std::vector<std::string> synonym_vector;
  std::string synonym = string_util::GetFirstWord(clause);
  if (synonym.empty()) {
    throw SyntaxErrorException();
  }
  synonym_vector.push_back(synonym);
  map.insert({kSynonymKey, synonym_vector});
  return map;
}

/*
 * Checks if a clause is a pattern clause
 */
bool Tokenizer::IsPattern(const std::string& clause) {
  size_t pattern_index = clause.find(kPatternStartIndicator);
  if (pattern_index == std::string::npos) {
    return false;
  }
  return true;
}

/*
 * Checks if a clause is a such that clause
 */
bool Tokenizer::IsSuchThat(const std::string& clause) {
  size_t index = clause.find(kSuchThatStartIndicator);
  if (index == std::string::npos) {
    return false;
  }
  return true;
}

/*
 * Searches for the start of subclauses (e.g. such that, pattern) and returns their index
 */
std::vector<size_t> Tokenizer::GetIndexListOfClauses(const std::string& statement) {
  std::vector<size_t> index_list;

  size_t such_that_index = statement.find(kSuchThatStartIndicator);
  if (such_that_index != std::string::npos) {
    index_list.push_back(such_that_index);
  }

  size_t pattern_index = statement.find(kPatternStartIndicator);
  if (pattern_index != std::string::npos) {
    index_list.push_back(pattern_index);
  }

  sort(index_list.begin(), index_list.end()); //sort ascending order

  return index_list;
}

/*
 * Parses for the such that clause and pattern clause in the clause and adds the synonym into the map.
 */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::AddSubclausesIntoMap(const std::string& statement,
                                                                                          std::unordered_map<std::string, std::vector<std::string>>& map) {

  std::string sub_clause;
  std::vector<std::string> such_that_statements;
  std::vector<std::string> pattern_statements;
  std::vector<size_t> index_list;

  index_list = GetIndexListOfClauses(statement);

  if (index_list.empty()) {
    map.insert({kSuchThatKey, such_that_statements});
    map.insert({kPatternKey, pattern_statements});
    return map;
  }

  index_list.push_back(statement.length());
  size_t start_index = 0;
  for (int i = 0; i < index_list.size()-1; i++) {
    size_t next_index = index_list[i+1];
    sub_clause = string_util::Trim(statement.substr(start_index,next_index));
    start_index = next_index;
    if (IsPattern(sub_clause)) {
      pattern_statements.push_back(sub_clause);
    } else if (IsSuchThat(sub_clause)) {
      such_that_statements.push_back(sub_clause);
    } else {
      continue;
    }
  }

  map.insert({kSuchThatKey, such_that_statements});
  map.insert({kPatternKey, pattern_statements});

  return map;
}


/*
 * Parses for the such that synonym, such that clause and pattern clause to add into the map.
 */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::AddSelectSubclausesIntoMap(const std::string& clause,
                                                                                                std::unordered_map<std::string, std::vector<std::string>>& map) {

  size_t select_index = clause.find(kSelectKeyword);
  if (select_index == std::string::npos) {
    throw SyntaxErrorException();
  }

  //Extract synonym
  std::string remaining_clause = string_util::GetClauseAfterKeyword(clause, kSelectKeyword);
  map = AddSynonymIntoMap(remaining_clause, map);

  //Extract other optional subclauses -- such that and pattern
  std::string synonym = map.at(kSynonymKey)[0];
  remaining_clause = string_util::GetClauseAfterKeyword(remaining_clause, synonym);

  map = AddSubclausesIntoMap(remaining_clause,map);

  return map;
}

/*
 * The tokenizer will tokenize the query into 5 subclauses: Declaration statements, Select Statements,
 * Synonym in Select statement, Such that clause and Pattern Clause.
 * Throws an exception if there is no Select Keyword.
 */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::TokenizeQuery(std::string query) {
  std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
  std::pair<std::vector<std::string>, std::string> declaration_select_pair;

  subclauses_map = AddDeclarationsAndStatementsIntoMap(std::move(query), subclauses_map);

  std::string select_statement = subclauses_map[kSelectKeyword][0];
  //Further Split Select statement into synonym, such that clause and pattern clause

  subclauses_map = AddSelectSubclausesIntoMap(select_statement, subclauses_map);

  return subclauses_map;
}

