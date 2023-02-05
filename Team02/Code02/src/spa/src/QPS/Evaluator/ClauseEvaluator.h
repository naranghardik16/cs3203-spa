#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/HashPair.h"
#include "PKB/Interfaces/PkbReadFacade.h"

class ClauseEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  SyntaxPair syntax_pair_;
  std::shared_ptr<PkbReadFacade> pkb_;

 public:
  ClauseEvaluator(Synonym synonym, Map declaration_map, SyntaxPair pair, std::shared_ptr<PkbReadFacade> pkb) {
    synonym_ = synonym;
    declaration_map_ = declaration_map;
    syntax_pair_ = pair;
    pkb_ = std::move(pkb);
  }

  Synonym GetSynonym();
  Map GetDeclarationMap();
  SyntaxPair GetSyntaxPair();
  std::shared_ptr<PkbReadFacade> GetPKB();

  virtual std::vector<std::vector<std::string>> EvaluateClause() = 0;

  virtual ~ClauseEvaluator() {};
};
