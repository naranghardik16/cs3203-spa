#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/HashPair.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include <memory>

class ClauseEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  SyntaxPair syntax_pair_;

 public:
  ClauseEvaluator(Synonym synonym, Map declaration_map, SyntaxPair pair) {
    synonym_ = synonym;
    declaration_map_ = declaration_map;
    syntax_pair_ = pair;
  }

  Synonym GetSynonym();
  Map GetDeclarationMap();
  SyntaxPair GetSyntaxPair();

  virtual std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) = 0;
  virtual bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) = 0;
  virtual ~ClauseEvaluator() {};
};
