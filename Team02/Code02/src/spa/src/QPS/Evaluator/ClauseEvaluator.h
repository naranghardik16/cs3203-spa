#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/HashPair.h"

class ClauseEvaluator {
 private:
  Synonym synonym_;
  Map declaration_map_;
  SyntaxPair syntax_pair_;

 public:
  ClauseEvaluator(Synonym synonym, Map declaration_map, SyntaxPair pair) {
    synonym_ = synonym;
    declaration_map_ = declaration_map_;
    syntax_pair_ = pair;
  }

  virtual PairConstraintSet EvaluateClause() = 0;

  virtual ~ClauseEvaluator() {};
};
