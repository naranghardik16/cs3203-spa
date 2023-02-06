#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class FollowsStarClauseEvaluator : public ClauseEvaluator {
 private:
  std::string relationship_reference_;
  std::string first_arg_;
  std::string second_arg_;
 public:
  FollowsStarClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) : ClauseEvaluator(s,d,syntax_pair, pkb) {
    relationship_reference_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second.first;
    second_arg_ = syntax_pair.second.second;
  }
  std::vector<std::vector<std::string>> EvaluateClause();
  bool IsBooleanConstraint();
  bool EvaluateBooleanConstraint();
};
