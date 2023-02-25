#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"

class AssignPatternClauseEvaluator : public ClauseEvaluator {
 private:
  std::string syn_assign_;
  std::string first_arg_;
  std::string second_arg_;
 public:
  AssignPatternClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
    syn_assign_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb);
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb);

  //Helper
  std::shared_ptr<Result> JoinWithAssignWithExactExpression(std::shared_ptr<Result> r, std::shared_ptr<PkbReadFacade> pkb);
  std::shared_ptr<Result> JoinWithAssignWithPartialExpression(std::shared_ptr<Result> r, std::shared_ptr<PkbReadFacade> pkb);
};
