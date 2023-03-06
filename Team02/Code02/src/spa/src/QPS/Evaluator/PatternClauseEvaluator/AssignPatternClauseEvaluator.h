#pragma once

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"
#include "core/model/Expression.h"

class AssignPatternClauseEvaluator : public ClauseEvaluator {
 private:
  std::string syn_assign_;
  std::string first_arg_;
  std::string second_arg_;
  std::shared_ptr<Expression> expression_;
 public:
  AssignPatternClauseEvaluator(Map d, SyntaxPair syntax_pair, std::shared_ptr<Expression> expr) : ClauseEvaluator(d) {
    syn_assign_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
    expression_ = expr;
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb);
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb);

  //Helper
  std::shared_ptr<Result> JoinWithAssignWithExactExpression(const std::shared_ptr<Result>& r, const std::shared_ptr<PkbReadFacade>& pkb);
  std::shared_ptr<Result> JoinWithAssignWithPartialExpression(const std::shared_ptr<Result>& r, const std::shared_ptr<PkbReadFacade>& pkb);
};
