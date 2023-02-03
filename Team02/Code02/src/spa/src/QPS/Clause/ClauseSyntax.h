#pragma once

#include <string>
#include <memory>
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Evaluator/ClauseEvaluator.h"

class ClauseSyntax {
 private:
  SyntaxPair pair_;
 public:
  explicit ClauseSyntax(SyntaxPair pair);
  std::string GetEntity();
  std::string GetFirstParameter();
  std::string GetSecondParameter();
  SyntaxPair GetSyntaxPair();

  virtual bool Equals(ClauseSyntax &other) = 0;
  virtual std::shared_ptr<ClauseEvaluator> CreateClauseEvaluator(Synonym s, Map declaration_map) = 0;
};
