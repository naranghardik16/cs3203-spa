#pragma once

#include <utility>

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
  std::string syn_;
  std::string first_arg_;
  std::string second_arg_;
  std::shared_ptr<Expression> expression_;

 public:
  PatternClauseEvaluator(Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb,
                         std::shared_ptr<Expression> expr) :
                         ClauseEvaluator(std::move(d), std::move(pkb)) {
    syn_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
    expression_ = std::move(expr);
  }

  bool EvaluateBooleanConstraint() override;
  std::shared_ptr<Result> EvaluateClause() override;

  virtual ResultTable HandleFirstArgSyn() = 0;
  virtual ResultTable HandleFirstArgWildcard() = 0;
  virtual ResultTable HandleFirstArgVariable() = 0;
  virtual std::shared_ptr<Result> HandlePartialMatch(const std::shared_ptr<Result>& r) = 0;
  virtual std::shared_ptr<Result> HandleExactMatch(const std::shared_ptr<Result>& r) = 0;
};
