#pragma once
#include "PKB/PKB.h"
#include "QPS/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"

class PqlEvaluator {
 private:
  std::shared_ptr<std::string> synonym_;
  std::shared_ptr<Map> declaration_map_;
  std::shared_ptr<ClauseSyntaxPtrList> syntax_pair_list_;
  std::shared_ptr<PkbReadFacade> pkb_;

 public:
  PqlEvaluator(ParserOutput* output, std::shared_ptr<PkbReadFacade> pkb) {
    synonym_ = std::make_shared<std::string>(output->first);
    declaration_map_ = std::make_shared<Map>(output->second.second);
    syntax_pair_list_ = std::make_shared<ClauseSyntaxPtrList>(output->second.first);
    pkb_ = pkb;
  }

  std::unordered_set<std::string> Evaluate();

  std::unordered_set<std::string> EvaluateTrivialSelectStatement();

};
