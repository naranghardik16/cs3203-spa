#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class ParentClauseEvaluator : public ClauseEvaluator {
 public:
  ParentClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) : ClauseEvaluator(s,d,syntax_pair, pkb) {}
  std::vector<std::vector<std::string>> EvaluateClause();
};
