//#pragma once
#include "QueryParser.h"
#include "QPS/Util/PQLConstants.h"
#include "Query.h"

std::shared_ptr<Query> QueryParser::ParseQuery(std::string query) {
  std::shared_ptr<Tokenizer> tk = std::make_shared<Tokenizer>();
  std::shared_ptr<QpsValidator> validator = std::make_shared<QpsValidator>();
  try {
    //!Split Query into declarations and select statement
    std::string query_trimmed = string_util::RemoveExtraWhitespacesInString(query);
    QueryStatementPair declaration_select_pair;

    //!Throws syntax error exception if either declarations or select statement is empty
    //! and if select statement does not start with Select keyword
    declaration_select_pair = tk->SplitQuery(query_trimmed);
    std::vector<std::string> declarations = declaration_select_pair.first;
    std::string trimmed_select_statement = declaration_select_pair.second;

    std::string remaining_clause = string_util::Trim(trimmed_select_statement.substr(pql_constants::kSelectKeyword.length()));
    //!Extract synonym -- throws a SyntaxErrorException if synonym does not adhere to synonym syntax
    Synonym synonym = tk->ParseSynonym(remaining_clause);
    remaining_clause = string_util::GetClauseAfterKeyword(remaining_clause, synonym);

    //!Extract syntax of subclauses -- throws a SyntaxErrorException if subclause does not adhere to syntax
    auto syntax_pair_list = tk->ParseSubClauses(remaining_clause);

    //!create declaration map -- extracts all the design entities and synonyms first then checks for syntax
    //!after checking for syntax, if there are repeated synonyms then semantic exception is thrown
    Map declaration_map = tk->ExtractAbstractSyntaxFromDeclarations(declarations);

    //syntax validation followed by semantic validation using Visitor pattern
    for (const std::shared_ptr<ClauseSyntax>& kClauseSyntax : syntax_pair_list) {
      validator->ValidateSubClause(declaration_map, kClauseSyntax);
    }

    //!consolidate parsing result
    std::shared_ptr<Query> query_ptr = std::make_shared<Query>(synonym, declaration_map, syntax_pair_list);
    return query_ptr;

  } catch (const SyntaxErrorException& e) {
  } catch (const SemanticErrorException& e) {
  }
}


