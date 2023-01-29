#pragma once
#include "Tokenizer.h"
#include "General/StringUtil.h"
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

//such that should have a relationship ref next e.g. "Modifies" etc which start with a letter
std::regex such_that_regex("such that [A-Z]");
// next token should be a syn-assign, which starts with a letter rather than , or ) e.g. (pattern, pattern)
std::regex pattern_regex("pattern [A-Za-z]");

const char kOpeningBracket = '(';
const char kClosingBracket = ')';
const char kComma = ',';


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

    std::string query_trimmed = string_util::RemoveExtraWhitespacesInString(query);
    size_t delimiter_index = query_trimmed.find(delimiter);
    while (delimiter_index != std::string::npos) {
      declaration = string_util::Trim(query_trimmed.substr(0, delimiter_index));
      declaration_statements.push_back(declaration);
      query_trimmed.erase(0, delimiter_index + delimiter.length());
      delimiter_index = query_trimmed.find(delimiter);
    }

    select_statements.push_back(string_util::Trim(query_trimmed));

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
 * Finds the start of a clause using regex.
 */
size_t Tokenizer::FindStartOfSubClauseIndex(std::string s, std::regex rgx) {
  std::smatch match;
  std::regex_search(s, match, rgx);
  if (match.empty()){
    return std::string::npos;
  }
  return s.find(match[0]);
}

/*
 * Searches for the start of subclauses (e.g. such that, pattern) and returns their index
 */
std::vector<size_t> Tokenizer::GetIndexListOfClauses(const std::string& statement) {
  std::vector<size_t> index_list;

  size_t such_that_index = FindStartOfSubClauseIndex(statement, such_that_regex);
  if (such_that_index != std::string::npos) {
    index_list.push_back(such_that_index);
  }


  size_t pattern_index = FindStartOfSubClauseIndex(statement, pattern_regex);
  if (pattern_index != std::string::npos) {
    index_list.push_back(pattern_index);
  }

  sort(index_list.begin(), index_list.end()); //sort ascending order

  return index_list;
}

/*
 * Parses for the such that clause and pattern clause in the clause and adds the synonym into the map.
 * */
std::unordered_map<std::string, std::vector<std::string>> Tokenizer::AddSubclausesIntoMap(const std::string& statement,
                                                                                          std::unordered_map<std::string, std::vector<std::string>>& map) {

  std::string sub_clause;
  std::vector<std::string> such_that_statements;
  std::vector<std::string> pattern_statements;
  std::vector<size_t> index_list;

  std::string statement_trimmed = string_util::RemoveExtraWhitespacesInString(statement);
  index_list = GetIndexListOfClauses(statement_trimmed);

  if (index_list.empty()) {
    map.insert({kSuchThatKey, such_that_statements});
    map.insert({kPatternKey, pattern_statements});
    return map;
  }

  index_list.push_back(statement_trimmed.length());
  size_t start_index = 0;
  for (int i = 0; i < index_list.size()-1; i++) {
    size_t next_index = index_list[i+1];
    sub_clause = string_util::Trim(statement_trimmed.substr(start_index,next_index));
    start_index = next_index;
    if (FindStartOfSubClauseIndex(sub_clause, pattern_regex) == 0) {
      pattern_statements.push_back(sub_clause);
    } else if (FindStartOfSubClauseIndex(sub_clause, such_that_regex) == 0) {
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

