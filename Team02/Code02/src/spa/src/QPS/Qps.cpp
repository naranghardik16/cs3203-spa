#include "Qps.h"

void Qps::ProcessQuery(std::string query, std::list<std::string> &results, std::shared_ptr<PkbReadFacade> pkb) {
  try {
    QueryParser parser;
    std::shared_ptr<Query> parsed_query = parser.ParseQuery(query);

    PqlEvaluator evaluator(parsed_query, pkb);
    std::unordered_set<std::string> result_set = evaluator.Evaluate();

    for (auto &kOut : result_set) {
      results.push_back(kOut);
    }
  } catch (const SyntaxErrorException& e) {
    results.push_back("SyntaxError");
  } catch (const SemanticErrorException& e) {
    results.push_back("SemanticError");
  }
}
