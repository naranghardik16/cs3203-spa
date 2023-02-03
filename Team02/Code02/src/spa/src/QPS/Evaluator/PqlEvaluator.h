#pragma once
#include "PKB.h"
#include "QPS/Query.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"

class PqlEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_pair_list_;
  std::shared_ptr<PkbReadFacade> pkb_;

 public:
  PqlEvaluator(std::shared_ptr<Query> parser_output, std::shared_ptr<PkbReadFacade> pkb);

  std::unordered_set<std::string> Evaluate();

  std::unordered_set<std::string> EvaluateTrivialSelectStatement();

};
