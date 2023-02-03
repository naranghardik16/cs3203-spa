#pragma once
#include "QpsTokenizer.h"
#include "General/StringUtil.h"
#include <utility>
#include "General/SpaException/SyntaxErrorException.h"
#include "QPS/Util/PQLConstants.h"
#include "General/SpaException/SemanticErrorException.h"
#include "Clause/SuchThatClauseSyntax.h"
#include "Clause/PatternClauseSyntax.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/QueryUtil.h"
#include "ExpressionParser.h"

QpsTokenizer::QpsTokenizer() : syntax_validator_(new ClauseSyntaxValidator()), semantic_validator_(new ClauseSemanticValidator()){}

/*
 * Splits the query_extra_whitespace_removed into declarations and select statement then adds this values into a map.
 * Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
QueryStatementPair QpsTokenizer::SplitQuery(const std::string& query_extra_whitespace_removed) {
  std::string delimiter = ";";
  std::vector<std::string> declaration_statements;
  std::string declaration;

  std::string temp = query_extra_whitespace_removed;
  size_t delimiter_index = temp.find(delimiter);
  while (delimiter_index != std::string::npos) {
    declaration = string_util::Trim(temp.substr(0, delimiter_index));
    declaration_statements.push_back(declaration);
    temp.erase(0, delimiter_index + delimiter.length());
    delimiter_index = temp.find(delimiter);
  }

  std::string select_statement = string_util::Trim(temp);

  if (declaration_statements.empty() || select_statement.empty()) {
    throw SyntaxErrorException();
  }
  if (select_statement.substr(0, pql_constants::kSelectKeyword.length()) != pql_constants::kSelectKeyword) {
    throw SyntaxErrorException();
  }

  QueryStatementPair declaration_select_statement_pair;
  declaration_select_statement_pair.first = declaration_statements;
  declaration_select_statement_pair.second = select_statement;
  return declaration_select_statement_pair;
}

/*
 * Finds the start of a clause using regex.
 */
size_t QpsTokenizer::FindStartOfSubClauseIndex(const std::string& substr_after_synonym, const std::regex& rgx) {
  std::smatch match;
  std::regex_search(substr_after_synonym, match, rgx);
  if (match.empty()){
    return std::string::npos;
  }
  return substr_after_synonym.find(match[0]);
}

/*
 * Searches for the start of subclauses (e.g. such that, pattern) and returns their index
 */
std::vector<size_t> QpsTokenizer::GetIndexListOfClauses(const std::string& statement) {
  std::vector<size_t> index_list;

  size_t such_that_index = FindStartOfSubClauseIndex(statement, pql_constants::kSuchThatRegex);
  if (such_that_index != std::string::npos) {
    index_list.push_back(such_that_index);
  }


  size_t pattern_index = FindStartOfSubClauseIndex(statement, pql_constants::kPatternRegex);
  if (pattern_index != std::string::npos) {
    index_list.push_back(pattern_index);
  }

  sort(index_list.begin(), index_list.end()); //sort ascending order

  return index_list;
}

/*
 * Extracts the synonym as a key and the corresponding design entity as the value in an unordered map for further validation.
 */
std::unordered_map<std::string, std::string> QpsTokenizer::ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations) {
  std::unordered_map<std::string, std::string> synonym_to_design_entity_map;
  std::string design_entity;

  for (const std::string &kDeclaration : declarations) {
    design_entity = string_util::GetFirstWord(kDeclaration);
    if (!QueryUtil::IsDesignEntity(design_entity)) {
      throw SyntaxErrorException();
    }
    std::string synonym_substring = string_util::GetClauseAfterKeyword(kDeclaration, design_entity);
    std::vector<std::string> synonym_list = string_util::SplitStringByDelimiter(synonym_substring, ",");
    for (const std::string &kSynonym : synonym_list) {
      if (!QueryUtil::IsSynonym(kSynonym)) {
        throw SyntaxErrorException();
      }
      if (synonym_to_design_entity_map.find(kSynonym) != synonym_to_design_entity_map.end()) {
        //we want to throw syntax exception first if there are any but this will mean that we will continue to loop and parse the declarations, which takes extra time
        semantic_validator_->has_semantic_error_ = true;
      }
      synonym_to_design_entity_map.insert({kSynonym, design_entity});
    }
  }
  semantic_validator_->declaration_ = synonym_to_design_entity_map;

  return synonym_to_design_entity_map;
}

/*
 * Parses for the synonym in the clause and adds the synonym into the map.
 */
std::string QpsTokenizer::ParseSynonym(const std::string& select_keyword_removed_clause) {
  std::vector<std::string> synonym_vector;
  std::string trimmed_select_keyword_removed_clause = string_util::Trim(select_keyword_removed_clause);
  std::string synonym = string_util::GetFirstWord(trimmed_select_keyword_removed_clause);
  if (!QueryUtil::IsSynonym(synonym)) {
    throw SyntaxErrorException();
  }
  return synonym;
}

/*
 * Extracts the entity (e.g. the relationship reference or the syn-assign), parameters in the relationship reference
 * from a such that clause or pattern clause.
 * Throws SyntaxErrorException if the concrete syntax in a such that clause cannot be found.
 * Returns an empty map if the clause is empty because it is optional to have a such that clause.
 */
SyntaxPair QpsTokenizer::ExtractAbstractSyntaxFromClause(const std::string& clause, const std::string& clause_start_indicator) {
  size_t start_of_rel_ref_index = clause.find(clause_start_indicator) + clause_start_indicator.length();
  size_t opening_bracket_index = clause.find(pql_constants::kOpeningBracket);
  size_t comma_index = clause.find(pql_constants::kComma);
  size_t closing_bracket_index = clause.find_last_of(pql_constants::kClosingBracket);

  //check for concrete syntax like ( , ) and keywords like such,that or pattern
  if ((start_of_rel_ref_index == std::string::npos) || (opening_bracket_index == std::string::npos) ||
      (comma_index == std::string::npos) || (closing_bracket_index == std::string::npos)) {
    throw SyntaxErrorException();
  }

  std::string relationship = string_util::Trim(clause.substr(start_of_rel_ref_index,
                                                             opening_bracket_index - start_of_rel_ref_index));
  std::string first_parameter = string_util::Trim(clause.substr(opening_bracket_index+1,

                                                                comma_index - (opening_bracket_index+1)));
  std::string second_parameter = string_util::Trim(clause.substr(comma_index+1,
                                                                 closing_bracket_index-(comma_index+1)));

  std::string remaining_clause = string_util::Trim(clause.substr(closing_bracket_index+1));

  if (!remaining_clause.empty()) {
    throw SyntaxErrorException();
  }

  SyntaxPair clause_syntax;
  ParameterPair parameters;
  parameters.first = first_parameter;
  parameters.second = second_parameter;
  clause_syntax.first = relationship;
  clause_syntax.second = parameters;

  return clause_syntax;
}

/*
 * Parses for the such that clause and pattern clause in the clause and adds the synonym into the map.
 * */
std::vector<std::shared_ptr<ClauseSyntax>> QpsTokenizer::ParseSubClauses(const std::string& statement) {

  std::string sub_clause;
  std::vector<size_t> index_list;
  std::vector<std::shared_ptr<ClauseSyntax>> syntax_pair_list;
  std::string statement_trimmed = string_util::RemoveExtraWhitespacesInString(statement);
  index_list = GetIndexListOfClauses(statement_trimmed);

  index_list.push_back(statement_trimmed.length());
  size_t start_index = 0;
  for (int i = 0; i < index_list.size()-1; i++) {
    size_t next_index = index_list[i+1];
    sub_clause = string_util::Trim(statement_trimmed.substr(start_index,next_index));
    start_index = next_index;
    if (FindStartOfSubClauseIndex(sub_clause, pql_constants::kPatternRegex) == 0) {
      SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause, pql_constants::kPatternStartIndicator);
      syntax.second.second = ExpressionParser::ParseExpressionSpec(syntax.second.second);
      std::shared_ptr<ClauseSyntax> pattern_syntax = std::make_shared<PatternClauseSyntax>(syntax);

      syntax_validator_->ValidatePatternClauseSyntax(pattern_syntax);
      semantic_validator_->ValidatePatternClauseSemantic(pattern_syntax);

      syntax_pair_list.push_back(pattern_syntax);
    } else if (FindStartOfSubClauseIndex(sub_clause, pql_constants::kSuchThatRegex) == 0) {
      SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause, pql_constants::kSuchThatStartIndicator);
      std::shared_ptr<ClauseSyntax> such_that_syntax = std::make_shared<SuchThatClauseSyntax>(syntax);

      syntax_validator_->ValidateSuchThatClauseSyntax(such_that_syntax);
      semantic_validator_->ValidateSuchThatClauseSemantic(such_that_syntax);

      syntax_pair_list.push_back(such_that_syntax);
    } else {
      continue;
    }
  }
  return syntax_pair_list;
}