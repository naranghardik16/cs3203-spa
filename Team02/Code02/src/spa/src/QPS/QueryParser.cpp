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
  Map declaration_map = tk->ExtractAbstractSyntaxFromDeclarations(declarations);

  //Already checked if the statement starts with Select
  std::string trimmed_select_statement = declaration_select_pair.second;
  std::string remaining_clause = string_util::Trim(trimmed_select_statement.substr(pql_constants::kSelectKeyword.length()));

  std::string syn_substring = tk->GetSynonymSubstring(remaining_clause);
  SelectedSynonymTuple synonym_tuple = tk->ParseSynonym(syn_substring, declaration_map);

  std::string clause_substring = tk->GetSubclauseSubstring(remaining_clause);
  ClauseSyntaxPtrList syntax_pair_list;
  if (!clause_substring.empty()) {
    syntax_pair_list = tk->ParseSubClauses(clause_substring);
  }

  //TODO to remove because will pass to validator in ParseSynonym to validate
  for (auto synonym : synonym_tuple) {
    if (declaration_map.find(synonym) == declaration_map.end() && !QueryUtil::IsAttrRef(synonym)) {
      throw SemanticErrorException();
    }
  }

  if (tk->semantic_validator_->has_semantic_error_) {
    throw SemanticErrorException();
  }

  //consolidate parsing result
  std::shared_ptr<Query> query_ptr = std::make_shared<Query>(synonym_tuple, declaration_map, syntax_pair_list);
  return query_ptr;
}
