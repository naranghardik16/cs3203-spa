#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class WithClauseEvaluator : public ClauseEvaluator {
 private:
  std::string first_arg_;
  std::string second_arg_;
 public:
  WithClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
    first_arg_ =  syntax_pair.second.first;
    second_arg_ = syntax_pair.second.second;
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb);
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb);
};

