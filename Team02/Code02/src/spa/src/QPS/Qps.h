#pragma once

#include <string>
#include <list>
#include <memory>
#include <unordered_set>
#include "QueryParser.h"
#include "Query.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "Evaluator/PqlEvaluator.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

/*!
 * The main driver class that will take in a query, parse the query and evaluate it
 * @param query is the input from user
 * @param results is to be populated by the evaluation results
 * @param pkb is to be used by QPS for evaluation of query
 */
class Qps {
 public:
  static void ProcessQuery(std::string query, std::list<std::string> &results, std::shared_ptr<PkbReadFacade> pkb);
};
