#include "Qps.h"

#include <utility>

void Qps::ProcessQuery(const std::string& query, std::list<std::string> &results, std::shared_ptr<PkbReadFacade> pkb) {
  try {
    QueryParser parser;
    std::shared_ptr<Query> parsed_query = parser.ParseQuery(query);

    PqlEvaluator evaluator(parsed_query, std::move(pkb));
    std::unordered_set<std::string> result_set = evaluator.Evaluate();

    for (auto &kOut : result_set) {
      results.push_back(kOut);
    }
  } catch (const SyntaxErrorException& e) {
    results.emplace_back("SyntaxError");
  } catch (const SemanticErrorException& e) {
    results.emplace_back("SemanticError");
  }
}
