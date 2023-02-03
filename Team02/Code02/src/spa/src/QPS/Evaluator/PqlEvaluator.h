#pragma once
#include "PKB.h"
#include "QPS/Query.h"
#include "QPS/Util/QPSTypeDefs.h"

class PqlEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_pair_list_;
  std::shared_ptr<PKB> pkb_ptr_;

 public:
  PqlEvaluator(std::shared_ptr<Query> parser_output, std::shared_ptr<PKB> pkb);

  std::unordered_set<std::string> Evaluate();

  std::unordered_set<std::string> EvaluateTrivialSelectStatement();

};
