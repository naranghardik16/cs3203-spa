#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class FollowsStarClauseEvaluator : public ClauseEvaluator {
 private:
  std::string relationship_reference_;
  std::string first_arg_;
  std::string second_arg_;
 public:
  FollowsStarClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
    relationship_reference_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second.first;
    second_arg_ = syntax_pair.second.second;
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb);
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb);
};
