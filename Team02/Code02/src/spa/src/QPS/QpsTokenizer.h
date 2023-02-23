#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <unordered_map>
#include "General/StringUtil.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/ClauseSyntaxValidator.h"
#include "QPS/ClauseSemanticValidator.h"

/*!
 * The tokenizer handles the parsing of the query
 * It works with ClauseSyntaxValidator and ClauseSemanticValidator to complete validation of the query
 */
class QpsTokenizer {

 public:
  std::shared_ptr<ClauseSyntaxValidator> syntax_validator_;
  std::shared_ptr<ClauseSemanticValidator> semantic_validator_;

  QpsTokenizer();

  /*!
 * Splits the query_extra_whitespace_removed into declarations and select statement then adds this values into a map.
 * Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 * @param query_extra_whitespace_removed is the query with any duplicate white space removed
 * @throws SyntaxErrorException if there is no Select statement or if there is no Select keyword in the Select statement
 */
  QueryLinesPair SplitQuery(const std::string& query_extra_whitespace_removed);

  /**
   * Parses for the synonym in the clause
   * @param clause with extra white space removed and has the Select keyword removed
   * @throws SyntaxErrorException if the synonym does not adhere to the lexical rules of being a synonym
   * @return synonym
   */
  SelectedSynonymTuple ParseSynonym(const std::string& clause);

  /**
   * Extracts the synonym as a key and the corresponding design entity as the value in an unordered map for semantic validation
   * and identification of synonym's design entity
   * @param declarations which is a vector of declaration statements
   * @throws SyntaxErrorException if the synonym does not follow lexical rules
   * @return a map where the synonym is the key and the corresponding design entity is the value
   */
  std::unordered_map<std::string, std::string> ExtractAbstractSyntaxFromDeclarations(const std::vector<std::string>& declarations);

  /**
   * Parses for different subclauses and creates ClauseSyntax derived classes
   * @param statement  which should only contain the subclauses and not be empty
   * @throws SyntaxErrorException if the subclauses are syntactically invalid
   * @throws SemanticErrorException if the subclauses have valid syntax but invalid semantics
   * @return a vector of ClauseSyntax
   */
  std::vector<std::shared_ptr<ClauseSyntax>> ParseSubClauses(const std::string &statement);

  /**
 * Finds the start of a clause using regex to find start of subclause indicators
  * Helper function to parse subclauses
 * @param clause which is the clause to check
 * @param rgx which is the regex of the start of subclause indicator to find
 * @return index of start of subclause if there is a match, else returns npos
 */
  size_t FindStartOfSubClauseIndex(const std::string& clause, const std::regex& rgx);

  /**
   * Searches for the start of subclauses (e.g. such that, pattern) and returns their index
   * Helper function to parse subclauses
   * @param statement which is not empty and contains only the subclauses
   * @throws SyntaxErrorException if there are no indexes found or if the first index is not 0
   * @return a vector of subclause start index to parse the subclauses
   */
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
  SyntaxPair ExtractAbstractSyntaxFromClause(const std::string& clause,const std::string& clause_start_indicator);

};
