//#pragma once
#include "QueryParser.h"
#include "QPS/Util/PQLConstants.h"
#include "Query.h"

std::shared_ptr<Query> QueryParser::ParseQuery(std::string query) {
  std::shared_ptr<QpsTokenizer> tk = std::make_shared<QpsTokenizer>();

  std::string query_trimmed = string_util::RemoveExtraWhitespacesInString(query);
  QueryLinesPair declaration_select_pair;

  declaration_select_pair = tk->SplitQuery(query_trimmed);
  std::vector<std::string> declarations = declaration_select_pair.first;
  std::string trimmed_select_statement = declaration_select_pair.second;

  std::string remaining_clause = string_util::Trim(trimmed_select_statement.substr(pql_constants::kSelectKeyword.length()));
  SelectedSynonymTuple synonym_tuple = tk->ParseSynonym(remaining_clause);
  //TODO to adjust the way remaining clause is obtained
  auto last_synonym = synonym_tuple.back(); // need to check if empty
  remaining_clause = string_util::GetSubStringAfterKeyword(remaining_clause, last_synonym);

  Map declaration_map = tk->ExtractAbstractSyntaxFromDeclarations(declarations);

  ClauseSyntaxPtrList syntax_pair_list;
  if (!remaining_clause.empty()) {
    syntax_pair_list = tk->ParseSubClauses(remaining_clause);
  }

  //TODO to directly pass to validator to validate instead of looping and checking declaration map
  //SelectSynonymSyntaxValidator->validate(synonym_tuple)
  //SelectSynonymSemanticValidator->validate(synonym_tuple)
  if (!synonym_tuple.empty()) {
    for (auto synonym : synonym_tuple) {
      if (declaration_map.find(synonym) ==
          declaration_map.end() || tk->semantic_validator_->has_semantic_error_) {
        throw SemanticErrorException();
      }
    }
  }

  //consolidate parsing result
  std::shared_ptr<Query> query_ptr = std::make_shared<Query>(synonym_tuple, declaration_map, syntax_pair_list);
  return query_ptr;
}
