#pragma once
#include "QpsTokenizer.h"
#include "General/StringUtil.h"
#include <utility>
#include "General/SpaException/SyntaxErrorException.h"
#include "QPS/Util/PQLConstants.h"
#include "Clause/SuchThatClauseSyntax.h"
#include "Clause/PatternClauseSyntax.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/QueryUtil.h"
#include "ExpressionParser.h"
#include "QPS/Clause/WithClauseSyntax.h"

QpsTokenizer::QpsTokenizer() : syntax_validator_(new ClauseSyntaxValidator()), semantic_validator_(new ClauseSemanticValidator()){}

QueryLinesPair QpsTokenizer::SplitQuery(const std::string& query_extra_whitespace_removed) {
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

  if (declaration_statements.empty()) {
    throw SyntaxErrorException("No declarations");
  }
  if (select_statement.empty()) {
    throw SyntaxErrorException("There is no select statement identified");
  }

  if (select_statement.substr(0, pql_constants::kSelectKeyword.length()) != pql_constants::kSelectKeyword) {
    throw SyntaxErrorException("There is no Select keyword in the Select statement");
  }

  QueryLinesPair declaration_select_statement_pair;
  declaration_select_statement_pair.first = declaration_statements;
  declaration_select_statement_pair.second = select_statement;
  return declaration_select_statement_pair;
}

size_t QpsTokenizer::FindEndOfSubClauseStart(const std::string& clause, const std::regex& rgx) {
  std::smatch match;
  std::regex_search(clause, match, rgx);
  if (match.empty()){
    return std::string::npos;
  }
  // -1 because regex matches an additional character after e.g. pattern a --> match
  // reason why we must match one more character is because a valid subclause start has to have an alphabet after it
  // and not e.g. a bracket or a comma, which could happen with repeated terminal names assign pattern, a; Select a such that Modifies(pattern,_)
  return clause.find(match[0]) + match[0].length()-1;
}


size_t QpsTokenizer::FindStartOfSubClauseStart(const std::string& clause, const std::regex& rgx) {
  std::smatch match;
  std::regex_search(clause, match, rgx);
  if (match.empty()){
    return std::string::npos;
  }
  return clause.find(match[0]);
}

std::vector<size_t> QpsTokenizer::FindIndexesOfClauseStart(const std::string& clause, const std::regex& rgx) {
  std::vector<size_t> index_list;
  for (sregex_iterator it = sregex_iterator(clause.begin(), clause.end(), rgx);
       it != sregex_iterator(); it++) {
    smatch match;
    match = *it;
    index_list.push_back(match.position(0));
  }
  return index_list;
}

std::vector<size_t> QpsTokenizer::GetIndexListOfClauses(const std::string& statement) {
  auto such_that_index_list = FindIndexesOfClauseStart(statement, pql_constants::kSuchThatRegex);
  auto pattern_index_list = FindIndexesOfClauseStart(statement, pql_constants::kPatternRegex);
  auto with_index_list = FindIndexesOfClauseStart(statement, pql_constants::kWithRegex);
  auto and_index_list = FindIndexesOfClauseStart(statement, pql_constants::kAndRegex);

  // preallocate memory
  std::vector<size_t> index_list;
  index_list.reserve(such_that_index_list.size() + pattern_index_list.size() + with_index_list.size() + and_index_list.size());
  index_list.insert(index_list.end(), such_that_index_list.begin(), such_that_index_list.end());
  index_list.insert(index_list.end(), pattern_index_list.begin(), pattern_index_list.end());
  index_list.insert(index_list.end(), with_index_list.begin(), with_index_list.end());
  index_list.insert(index_list.end(), and_index_list.begin(), and_index_list.end());

  sort(index_list.begin(), index_list.end()); //sort ascending order

  //! if index list is empty then the subclauses do not contain the valid subclause markers like "such that"
  if (index_list.empty()) {
    throw SyntaxErrorException("Tokenizer GetIndexListOfSubclauses: No valid subclauses could be parsed out");
  }
  //! If there are subclauses, then we should have a sub-clause start index at 0 and not e.g. at index 5
  if (index_list[0] > 0) {
    throw SyntaxErrorException("Tokenizer GetIndexListOfSubclauses: Invalid subclause present");
  }

  return index_list;
}

std::unordered_map<std::string, std::string> QpsTokenizer::ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations) {
  std::unordered_map<std::string, std::string> synonym_to_design_entity_map;
  std::string design_entity;

  for (const std::string &kDeclaration : declarations) {
    design_entity = string_util::GetFirstWord(kDeclaration);

    if (!QueryUtil::IsDesignEntity(design_entity)) {
      throw SyntaxErrorException("The design entity does not adhere to the lexical rules of design entity");
    }
    std::string synonym_substring = string_util::GetSubStringAfterKeyword(kDeclaration, design_entity);
    if (synonym_substring.empty()) {
      throw SyntaxErrorException("Missing synonym in declaration");
    }
    std::vector<std::string> synonym_list = string_util::SplitStringByDelimiter(synonym_substring, ",");
    for (const std::string &kSynonym : synonym_list) {
      if (!QueryUtil::IsSynonym(kSynonym)) {
        throw SyntaxErrorException("The synonym in the declaration does not adhere to the lexical rules of being a synonym");
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

SelectedSynonymTuple QpsTokenizer::ParseSynonym(const std::string& select_keyword_removed_clause) {
  std::string trimmed_select_keyword_removed_clause = string_util::Trim(select_keyword_removed_clause);
  std::string first_word = string_util::GetFirstWord(trimmed_select_keyword_removed_clause);
  char first_char = first_word[0];
  SelectedSynonymTuple synonym_vector;
  //! BOOLEAN case
  if ((first_word == pql_constants::kSelectBoolean)) {
    synonym_vector = {};
  } else if (first_char == pql_constants::kTupleOpeningBracket) {
    //! Multiple elem case
    synonym_vector = ParseForMultipleSynonyms(trimmed_select_keyword_removed_clause);
  } else {
    //! Single elem case -- synonym should be the first word e.g. Select a
    synonym_vector = {first_word};
  }

  //TODO to directly pass to validator to validate instead of looping and checking declaration map
  //SelectSynonymSyntaxValidator->validate(synonym_tuple)
  //SelectSynonymSemanticValidator->validate(synonym_tuple)
  if (!synonym_vector.empty()) {
    for (auto synonym : synonym_vector) {
      if (!QueryUtil::IsSynonym(synonym)) {
        throw SyntaxErrorException();
      }
    }
  }
  return synonym_vector;
}

SelectedSynonymTuple QpsTokenizer::ParseForMultipleSynonyms(std::string trimmed_select_keyword_removed_clause) {
  SelectedSynonymTuple synonym_vector;
  size_t closing_tuple_bracket_index = trimmed_select_keyword_removed_clause.find(pql_constants::kTupleClosingBracket);
  if (closing_tuple_bracket_index == std::string::npos) {
    throw SyntaxErrorException("No closing bracket for tuple");
  }
  // condition to run this function is that < is at index 0
  std::string synonyms_seperated_by_comma_substr = string_util::Trim(trimmed_select_keyword_removed_clause.substr(1,
                                                                                                                  closing_tuple_bracket_index-1));
  synonym_vector = string_util::SplitStringByDelimiter(synonyms_seperated_by_comma_substr, ",");
  return synonym_vector;
}

std::string QpsTokenizer::GetRemainingClauseAfterSynonym(std::string select_keyword_removed_clause) {
  std::string end_of_syn_marker;
  std::string first_word = string_util::GetFirstWord(select_keyword_removed_clause);
  char first_char = first_word[0];
  if (first_word == pql_constants::kSelectBoolean) {
    end_of_syn_marker = pql_constants::kSelectBoolean;
  } else if (first_char == pql_constants::kTupleOpeningBracket) {
    //! Multiple elem case
    end_of_syn_marker.append(1, pql_constants::kTupleClosingBracket);
  } else {
    //! Single elem case -- synonym should be the first word e.g. Select a
    end_of_syn_marker = first_word;
  }
  return string_util::GetSubStringAfterKeyword(select_keyword_removed_clause, end_of_syn_marker);
}

SyntaxPair QpsTokenizer::ExtractAbstractSyntaxFromClause(const std::string& clause, const std::regex& rgx) {
  size_t start_of_rel_ref_index = FindEndOfSubClauseStart(clause, rgx);
  size_t opening_bracket_index = clause.find(pql_constants::kOpeningBracket);
  size_t comma_index = clause.find(pql_constants::kComma);
  size_t closing_bracket_index = clause.find_last_of(pql_constants::kClosingBracket);

  //check for concrete syntax like ( , ) and keywords like such that or pattern
  if ((start_of_rel_ref_index == std::string::npos) || (opening_bracket_index == std::string::npos) ||
      (comma_index == std::string::npos) || (closing_bracket_index == std::string::npos)) {
    throw SyntaxErrorException("There is syntax error with the subclauses");
  }

  std::string relationship = string_util::Trim(clause.substr(start_of_rel_ref_index,
                                                             opening_bracket_index - start_of_rel_ref_index));
  std::string first_parameter = string_util::Trim(clause.substr(opening_bracket_index+1,

                                                                comma_index - (opening_bracket_index+1)));
  std::string second_parameter = string_util::Trim(clause.substr(comma_index+1,
                                                                 closing_bracket_index-(comma_index+1)));

  std::string remaining_clause = string_util::Trim(clause.substr(closing_bracket_index+1));

  if (!remaining_clause.empty()) {
    throw SyntaxErrorException("There is syntax error with the subclauses and remaining characters that remain unparsed");
  }

  if (QueryUtil::IsQuoted(first_parameter)) {
    first_parameter = "\"" + string_util::Trim(first_parameter.substr(1, first_parameter.length() - 2)) + "\"";
  }
  if (QueryUtil::IsQuoted(second_parameter)) {
    second_parameter = "\"" + string_util::Trim(second_parameter.substr(1, second_parameter.length() - 2)) + "\"";
  }

  SyntaxPair clause_syntax;
  ParameterPair parameters;
  parameters.first = first_parameter;
  parameters.second = second_parameter;
  clause_syntax.first = relationship;
  clause_syntax.second = parameters;

  return clause_syntax;
}


SyntaxPair QpsTokenizer::ExtractAbstractSyntaxFromWithClause(const std::string& clause, const std::regex& rgx) {
  size_t start_of_attrCond_index = FindEndOfSubClauseStart(clause, rgx);
  size_t equal_index = clause.find(pql_constants::kEqual);

  //check for concrete syntax like ( , ) and keywords like such that or pattern
  if ((start_of_attrCond_index == std::string::npos) || (equal_index == std::string::npos)) {
    throw SyntaxErrorException("There is syntax error with the subclauses");
  }

  std::string first_parameter = string_util::Trim(clause.substr(start_of_attrCond_index+1,
                                                                equal_index - (start_of_attrCond_index+1)));
  std::string second_parameter = string_util::Trim(clause.substr(equal_index+1));

  if (QueryUtil::IsQuoted(first_parameter)) {
    first_parameter = "\"" + string_util::Trim(first_parameter.substr(1, first_parameter.length() - 2)) + "\"";
  }
  if (QueryUtil::IsQuoted(second_parameter)) {
    second_parameter = "\"" + string_util::Trim(second_parameter.substr(1, second_parameter.length() - 2)) + "\"";
  }

  SyntaxPair clause_syntax;
  ParameterPair parameters;
  parameters.first = first_parameter;
  parameters.second = second_parameter;
  clause_syntax.first = "";
  clause_syntax.second = parameters;

  return clause_syntax;
}

std::vector<std::shared_ptr<ClauseSyntax>> QpsTokenizer::ParseSubClauses(const std::string& statement) {
  std::string sub_clause;
  std::vector<size_t> index_list;
  std::vector<std::shared_ptr<ClauseSyntax>> syntax_pair_list;
  std::string statement_trimmed = string_util::RemoveExtraWhitespacesInString(statement);
  index_list = GetIndexListOfClauses(statement_trimmed);
  index_list.push_back(statement_trimmed.length());

  std::regex previous_matched_regex;
  size_t start_index = 0;
  for (int i = 0; i < index_list.size()-1; i++) {
    size_t next_index = index_list[i+1];
    sub_clause = string_util::Trim(statement_trimmed.substr(start_index,next_index));
    start_index = next_index;

    if (FindStartOfSubClauseStart(sub_clause, pql_constants::kPatternRegex) == 0) {
      SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause, pql_constants::kPatternRegex);
      syntax.second.second = ExpressionParser::ParseExpressionSpec(syntax.second.second);
      std::shared_ptr<ClauseSyntax> pattern_syntax = std::make_shared<PatternClauseSyntax>(syntax);

      syntax_validator_->ValidatePatternClauseSyntax(pattern_syntax);
      semantic_validator_->ValidatePatternClauseSemantic(pattern_syntax);

      syntax_pair_list.push_back(pattern_syntax);
      previous_matched_regex = pql_constants::kPatternRegex;
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kSuchThatRegex) == 0) {
      SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause, pql_constants::kSuchThatRegex);
      std::shared_ptr<ClauseSyntax> such_that_syntax = std::make_shared<SuchThatClauseSyntax>(syntax);

      syntax_validator_->ValidateSuchThatClauseSyntax(such_that_syntax);
      semantic_validator_->ValidateSuchThatClauseSemantic(such_that_syntax);

      syntax_pair_list.push_back(such_that_syntax);
      previous_matched_regex = pql_constants::kSuchThatRegex;
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kWithRegex) == 0) {
      SyntaxPair syntax = ExtractAbstractSyntaxFromWithClause(sub_clause, pql_constants::kWithRegex);
      std::shared_ptr<ClauseSyntax> with_syntax = std::make_shared<WithClauseSyntax>(syntax);

      //syntax_validator_->ValidateWithClauseSyntax(such_that_syntax);
      //semantic_validator_->ValidateWithClauseSemantic(such_that_syntax);

      syntax_pair_list.push_back(with_syntax);
      previous_matched_regex = pql_constants::kWithRegex;
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kAndRegex) == 0) {
    } else {
      throw SyntaxErrorException("There is an invalid subclause"); //e.g. pattern a(_,_)  suchs that
    }
  }

  return syntax_pair_list;
}
