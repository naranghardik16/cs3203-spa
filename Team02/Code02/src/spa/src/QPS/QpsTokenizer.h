#pragma once

#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <utility>
#include <unordered_map>
#include "General/StringUtil.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/SyntaxValidator.h"
#include "QPS/SemanticValidator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "QPS/Util/PQLConstants.h"
#include "Clause/SuchThatClauseSyntax.h"
#include "Clause/PatternClauseSyntax.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Clause/WithClauseSyntax.h"

/*!
 * The tokenizer handles the parsing of the query
 * It works with SyntaxValidator and SemanticValidator to complete validation of the query
 */
class QpsTokenizer {

 public:
  std::shared_ptr<SyntaxValidator> syntax_validator_;
  std::shared_ptr<SemanticValidator> semantic_validator_;

  QpsTokenizer();

  /*!
 * Splits the query_extra_whitespace_removed into declarations and select statement then adds this values into a map.
 * Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 * @param query_extra_whitespace_removed is the query with any duplicate white space removed
 * @throws SyntaxErrorException if there is no Select statement or if there is no Select keyword in the Select statement
 */
  QueryLinesPair SplitQuery(const std::string& query_extra_whitespace_removed);

  /**
   * Parses for the synonym in the clause_with_select_removed
   * @param clause_with_select_removed with extra white space removed and has the Select keyword removed
   * @throws SyntaxErrorException if the synonym does not adhere to the lexical rules of being a synonym
   * @return synonym
   */
  SelectedSynonymTuple ParseSynonym(const std::string& clause_with_select_removed, Map declaration_map);

  /**
   * Extracts the synonym as a key and the corresponding design entity as the value in an unordered map for semantic validation
   * and identification of synonym's design entity
   * @param declarations which is a vector of declaration statements
   * @throws SyntaxErrorException if the synonym does not follow lexical rules
   * @return a map where the synonym is the key and the corresponding design entity is the value
   */
  std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations) const;

  /**
   * Parses for different subclauses and creates ClauseSyntax derived classes
   * @param statement  which should only contain the subclauses and not be empty
   * @throws SyntaxErrorException if the subclauses are syntactically invalid
   * @throws SemanticErrorException if the subclauses have valid syntax but invalid semantics
   * @return a vector of ClauseSyntax
   */
  std::vector<std::shared_ptr<ClauseSyntax>> ParseSubClauses(const std::string &statement);

  std::vector<size_t> GetIndexListOfClauses(const std::string& statement);

  /**
   * Extracts the entity (e.g. the relationship reference or the syn-assign), parameters in the relationship reference
   * from a subclause
   * Helper function to parse subclauses
   * @param clause should be trimmed and have duplicate white spaces removed already
   * @param clause_start_indicator
   * @throws SyntaxErrorException if the concrete syntax in a such that clause cannot be found or if there are extra characters after the subclause
   * @return a SyntaxPair which contains the entity and the arguments
  */
  SyntaxPair ExtractAbstractSyntaxFromClause(const std::string& clause);
  SelectedSynonymTuple ParseForMultipleSynonyms(const std::string& trimmed_select_keyword_removed_clause);
  size_t FindIndexOfRegexMatch(const std::string &clause, const regex &rgx);
  size_t FindEndOfSubClauseStart(const std::string &clause, const regex &rgx);
  SyntaxPair ExtractAbstractSyntaxFromWithClause(const std::string &clause);
  shared_ptr<ClauseSyntax> MakePatternClauseSyntax(const std::string& sub_clause);
  shared_ptr<ClauseSyntax> MakeSuchThatClauseSyntax(const std::string &sub_clause);
  shared_ptr<ClauseSyntax> MakeWithClauseSyntax(const std::string &sub_clause);
  shared_ptr<ClauseSyntax> MakeAndClauseSyntax(const std::string &sub_clause, const string &previous_sub_clause);
  pair<string, string> ProcessIDENT(std::string first_parameter, std::string second_parameter);
  std::string ParseIDENT(const std::string& parameter);
  ParameterVector ParseParameters(const std::string& parameters_substr);
  std::string GetSynonymSubstring(std::string select_keyword_removed_clause);
  std::string ParseAttrRef(const std::string& attr_ref);
  SelectedSynonymTuple ParseSingleSynonym(const std::string& clause_after_syn);
  std::string GetSubclauseString(const std::string& clause_with_select_removed, SelectedSynonymTuple syn_vector);
  std::string ParseWithClauseParameter(std::string parameter);
  std::string GetRegexMatch(const std::string &clause, const regex &rgx);
  SelectedSynonymTuple HandleSingleAttrRef(const std::string &syn, const std::string &clause_after_syn);
};
