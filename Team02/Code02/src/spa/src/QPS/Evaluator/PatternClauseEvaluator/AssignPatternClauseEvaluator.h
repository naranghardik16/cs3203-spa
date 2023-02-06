#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"

class AssignPatternClauseEvaluator : public ClauseEvaluator {
 private:
  std::string syn_assign_;
  std::string first_arg_;
  std::string second_arg_;
 public:
  AssignPatternClauseEvaluator(Synonym s, Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) : ClauseEvaluator(s,d,syntax_pair, pkb) {
    syn_assign_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second.first;
    second_arg_ = syntax_pair.second.second;
  }
  std::vector<std::vector<std::string>> EvaluateClause();
  bool IsBooleanConstraint();
  bool EvaluateBooleanConstraint();
};
