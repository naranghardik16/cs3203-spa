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
  std::string delimiter = pql_constants::kSemicolon;
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

  std::vector<size_t> index_list;
  // preallocate memory
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
  std::unordered_map<std::string, std::string> synonym_to_design_entity_map = {};
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

std::string QpsTokenizer::ParseIDENT(std::string parameter) {
  return "\"" + string_util::Trim(parameter.substr(1, parameter.length() - 2)) + "\"";
}


std::string QpsTokenizer::GetSynonymFromAttrRef(std::string attr_ref) {
  size_t index_of_fullstop = attr_ref.find(pql_constants::kFullStop);
  std::string synonym = string_util::Trim(attr_ref.substr(0, index_of_fullstop));
  return synonym;
}

std::string QpsTokenizer::GetAttrName(std::string attr_ref) {
  size_t index_of_fullstop = attr_ref.find(pql_constants::kFullStop);
  std::string attrName = string_util::Trim(attr_ref.substr(index_of_fullstop+1));
  return attrName;
}

std::string QpsTokenizer::ParseAttrRef(std::string attr_ref) {
  std::string synonym = GetSynonymFromAttrRef(attr_ref);
  std::string attrName = GetAttrName(attr_ref);
  return synonym + "." + attrName;
}

SelectedSynonymTuple QpsTokenizer::ParseSingleSynonym(std::string syn_substring) {
  SelectedSynonymTuple synonym_vector;

  std::string syn = string_util::GetFirstWord(syn_substring);
  std::string clause_after_first_word = string_util::GetSubStringAfterKeyword(syn_substring, syn);

  std::string attrName;
  auto first_char = clause_after_first_word.substr(0, 1);
  if (first_char == pql_constants::kFullStop) {
    attrName = string_util::Trim(clause_after_first_word.substr(1));
    synonym_vector = {syn + "." + attrName};
  } else {
    synonym_vector = {syn};
  }
  return synonym_vector;
}

SelectedSynonymTuple QpsTokenizer::ParseSynonym(const std::string& clause_with_select_removed, Map declaration_map) {
  std::string first_word = string_util::GetFirstWord(clause_with_select_removed);
  std::string clause_after_first_word = string_util::GetSubStringAfterKeyword(clause_with_select_removed, first_word);
  SelectedSynonymTuple synonym_vector;
  //! BOOLEAN case
  if ((first_word == pql_constants::kSelectBoolean) && (declaration_map.find(first_word) == declaration_map.end())) {
    synonym_vector = {};
  } else if (first_word.substr(0,1) == pql_constants::kTupleOpeningBracket) {
    //! Multiple elem case
    synonym_vector = ParseForMultipleSynonyms(clause_with_select_removed);
  } else {
    synonym_vector = ParseSingleSynonym(clause_with_select_removed);
  }

  //TODO to directly pass to validator to validate instead of looping and checking declaration map
  //SelectSynonymSyntaxValidator->validate(synonym_tuple)
  //SelectSynonymSemanticValidator->validate(synonym_tuple)
  if (!synonym_vector.empty()) {
    for (auto syn : synonym_vector) {
      if (!QueryUtil::IsSynonym(syn) && !QueryUtil::IsAttrRef(syn)) {
        throw SyntaxErrorException("Not a valid syn or attr-ref");
      }
    }
  }

  return synonym_vector;
}

std::string QpsTokenizer::GetSubclauseString(std::string clause_with_select_removed, SelectedSynonymTuple syn_vector) {
  std::string first_word = string_util::GetFirstWord(clause_with_select_removed);
  std::string remaining_clause;
  size_t index_start;
  //! BOOLEAN case
  if ((first_word == pql_constants::kSelectBoolean)) {
    index_start = clause_with_select_removed.find(pql_constants::kSelectBoolean) + pql_constants::kSelectBoolean.size();
  } else if (first_word.substr(0,1) == pql_constants::kTupleOpeningBracket) {
    //! Multiple elem case
    index_start = clause_with_select_removed.find(pql_constants::kTupleClosingBracket) + pql_constants::kTupleClosingBracket.size();
  } else {
    auto syn = syn_vector[0];
    if (QueryUtil::IsAttrRef(syn)) {
      auto attrName = GetAttrName(syn);
      index_start = clause_with_select_removed.find(attrName) + attrName.size();
    } else {
      index_start = clause_with_select_removed.find(syn) + syn.size();
    }
  }
  remaining_clause = string_util::Trim(clause_with_select_removed.substr(index_start));
  return remaining_clause;
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

  synonym_vector = string_util::SplitStringByDelimiter(synonyms_seperated_by_comma_substr, pql_constants::kComma);

  for (int i = 0; i < synonym_vector.size(); i++) {
    auto synonym = synonym_vector[i];
    if (QueryUtil::IsAttrRef(synonym)) {
      synonym_vector[i] = ParseAttrRef(synonym);
    }
  }

  return synonym_vector;
}

ParameterVector QpsTokenizer::ParseParameters(std::string parameters_substr) {
  ParameterVector parameters;
  Parameter parameter = "";
  size_t delimiter_index = parameters_substr.find(pql_constants::kComma);
  while (delimiter_index != std::string::npos) {
    parameter = string_util::Trim(parameters_substr.substr(0, delimiter_index));
    if (QueryUtil::IsQuoted(parameter)) {
      parameter = ParseIDENT(parameter);
    }
    parameters.push_back(parameter);
    parameters_substr.erase(0, delimiter_index + pql_constants::kComma.length());
    delimiter_index = parameters_substr.find(pql_constants::kComma);
  }

  parameter = string_util::Trim(parameters_substr);
  if (QueryUtil::IsQuoted(parameter)) {
    parameter = ParseIDENT(parameter);
  }
  parameters.push_back(parameter);

  return parameters;
}

SyntaxPair QpsTokenizer::ExtractAbstractSyntaxFromClause(const std::string& clause) {
  size_t opening_bracket_index = clause.find(pql_constants::kOpeningBracket);
  size_t comma_index = clause.find(pql_constants::kComma);
  size_t closing_bracket_index = clause.find_last_of(pql_constants::kClosingBracket);

  //check for concrete syntax like ( , ) and keywords like such that or pattern
  if ((opening_bracket_index == std::string::npos) ||
      (comma_index == std::string::npos) || (closing_bracket_index == std::string::npos)) {
    throw SyntaxErrorException("There is syntax error with the such that or pattern subclauses");
  }

  std::string relationship = string_util::Trim(clause.substr(0,
                                                             opening_bracket_index));
  std::string parameters_substr = string_util::Trim(clause.substr(opening_bracket_index+1,closing_bracket_index-(opening_bracket_index+1)));

  auto parameters = ParseParameters(parameters_substr);

  std::string remaining_clause = string_util::Trim(clause.substr(closing_bracket_index+1));

  if (!remaining_clause.empty()) {
    throw SyntaxErrorException("There is syntax error with the subclauses and remaining characters that remain unparsed");
  }

  SyntaxPair clause_syntax;
  clause_syntax.first = relationship;
  clause_syntax.second = parameters;
  return clause_syntax;
}


SyntaxPair QpsTokenizer::ExtractAbstractSyntaxFromWithClause(const std::string& clause) {
  size_t equal_index = clause.find(pql_constants::kEqual);

  //check for concrete syntax like ( , ) and keywords like such that or pattern
  if (equal_index == std::string::npos) {
    throw SyntaxErrorException("There is no = in the subclause");
  }

  std::string first_parameter = string_util::Trim(clause.substr(0,equal_index));
  std::string second_parameter = string_util::Trim(clause.substr(equal_index+1));

  if (QueryUtil::IsQuoted(first_parameter)) {
    first_parameter = "\"" + string_util::Trim(first_parameter.substr(1, first_parameter.length() - 2)) + "\"";
  }
  if (QueryUtil::IsQuoted(second_parameter)) {
    second_parameter = "\"" + string_util::Trim(second_parameter.substr(1, second_parameter.length() - 2)) + "\"";
  }

  SyntaxPair clause_syntax;
  ParameterVector parameters;
  parameters.push_back(first_parameter);
  parameters.push_back(second_parameter);
  clause_syntax.first = "";
  clause_syntax.second = parameters;

  return clause_syntax;
}

std::shared_ptr<ClauseSyntax> QpsTokenizer::MakePatternClauseSyntax(std::string sub_clause) {

  SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause);
  syntax.second[1] = ExpressionParser::ParseExpressionSpec(syntax.second[1]);
  std::shared_ptr<ClauseSyntax> pattern_syntax = std::make_shared<PatternClauseSyntax>(syntax);

  syntax_validator_->ValidatePatternClauseSyntax(pattern_syntax);
  semantic_validator_->ValidatePatternClauseSemantic(pattern_syntax);

  return pattern_syntax;
}

std::shared_ptr<ClauseSyntax> QpsTokenizer::MakeSuchThatClauseSyntax(std::string sub_clause) {
  SyntaxPair syntax = ExtractAbstractSyntaxFromClause(sub_clause);
  std::shared_ptr<ClauseSyntax> such_that_syntax = std::make_shared<SuchThatClauseSyntax>(syntax);

  syntax_validator_->ValidateSuchThatClauseSyntax(such_that_syntax);
  semantic_validator_->ValidateSuchThatClauseSemantic(such_that_syntax);

  return such_that_syntax;
}

std::shared_ptr<ClauseSyntax> QpsTokenizer::MakeWithClauseSyntax(std::string sub_clause) {
  SyntaxPair syntax = ExtractAbstractSyntaxFromWithClause(sub_clause);
  std::shared_ptr<ClauseSyntax> with_syntax = std::make_shared<WithClauseSyntax>(syntax);
  //syntax_validator_->ValidateWithClauseSyntax(with_syntax);
  //semantic_validator_->ValidateWithClauseSemantic(with_syntax);
  return with_syntax;
}

std::shared_ptr<ClauseSyntax> QpsTokenizer::MakeAndClauseSyntax(std::string sub_clause, std::string previous_sub_clause) {

  if (FindStartOfSubClauseStart(previous_sub_clause, pql_constants::kPatternRegex) == 0) {
    return MakePatternClauseSyntax(sub_clause);
  } else if (FindStartOfSubClauseStart(previous_sub_clause, pql_constants::kSuchThatRegex) == 0) {
    return MakeSuchThatClauseSyntax(sub_clause);
  } else if (FindStartOfSubClauseStart(previous_sub_clause, pql_constants::kWithRegex) == 0) {
    return MakeWithClauseSyntax(sub_clause);
  } else {
    throw SyntaxErrorException("There is no clause before the and clause");
  }
}

std::vector<std::shared_ptr<ClauseSyntax>> QpsTokenizer::ParseSubClauses(const std::string& statement) {
  std::string sub_clause;
  std::vector<size_t> index_list;
  std::vector<std::shared_ptr<ClauseSyntax>> syntax_pair_list;
  std::string statement_trimmed = string_util::RemoveExtraWhitespacesInString(statement);
  index_list = GetIndexListOfClauses(statement_trimmed);
  index_list.push_back(statement_trimmed.length());

  size_t start_index = 0;
  std::string previous_sub_clause;
  std::string processed_sub_clause;
  for (int i = 0; i < index_list.size()-1; i++) {
    size_t next_index = index_list[i+1];
    sub_clause = string_util::Trim(statement_trimmed.substr(start_index,next_index-start_index));
    start_index = next_index;

    if (FindStartOfSubClauseStart(sub_clause, pql_constants::kPatternRegex) == 0) {
      previous_sub_clause = sub_clause;
      processed_sub_clause =  sub_clause.substr(FindEndOfSubClauseStart(sub_clause, pql_constants::kPatternRegex));
      auto pattern_syntax = MakePatternClauseSyntax(processed_sub_clause);
      syntax_pair_list.push_back(pattern_syntax);
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kSuchThatRegex) == 0) {
      previous_sub_clause = sub_clause;
      processed_sub_clause =  sub_clause.substr(FindEndOfSubClauseStart(sub_clause, pql_constants::kSuchThatRegex));
      auto such_that_syntax = MakeSuchThatClauseSyntax(processed_sub_clause);
      syntax_pair_list.push_back(such_that_syntax);
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kWithRegex) == 0) {
      previous_sub_clause = sub_clause;
      processed_sub_clause =  sub_clause.substr(FindEndOfSubClauseStart(sub_clause, pql_constants::kWithRegex));
      auto with_syntax = MakeWithClauseSyntax(processed_sub_clause);
      syntax_pair_list.push_back(with_syntax);
    } else if (FindStartOfSubClauseStart(sub_clause, pql_constants::kAndRegex) == 0) {
      processed_sub_clause =  sub_clause.substr(FindEndOfSubClauseStart(sub_clause, pql_constants::kAndRegex));
      if (previous_sub_clause.empty()) {
        throw SyntaxErrorException("The first clause cannot be an and clause");
      }
      auto and_syntax = MakeAndClauseSyntax(processed_sub_clause, previous_sub_clause);
      syntax_pair_list.push_back(and_syntax);
    } else {
      throw SyntaxErrorException("There is an invalid subclause"); //e.g. such that pattern a(_,_)
    }
  }

  return syntax_pair_list;
}
