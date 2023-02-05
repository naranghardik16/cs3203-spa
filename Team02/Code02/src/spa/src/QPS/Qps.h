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

class Qps {
 public:
  static void ProcessQuery(std::string query, std::list<std::string> &results, std::shared_ptr<PkbReadFacade> pkb);
};
