#pragma once

#include <utility>

#include "QPS/Evaluator/PatternClauseEvaluator/PatternClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"
#include "core/model/Expression.h"
#include "ExpressionSpecEvaluator.h"

class AssignPatternClauseEvaluator : public PatternClauseEvaluator, public ExpressionSpecEvaluator {
 protected:
  std::shared_ptr<Expression> expression_;
 public:
  AssignPatternClauseEvaluator(Map d,
                               SyntaxPair syntax_pair,
                               std::shared_ptr<PkbReadFacade> pkb,
                               std::shared_ptr<Expression> expr
                               ) : PatternClauseEvaluator(std::move(d), std::move(syntax_pair),
                                                          std::move(pkb)) {
    expression_ = std::move(expr);
  }

  std::shared_ptr<Result> EvaluateClause() override;
  ResultTable HandleFirstArgSyn() override;
  ResultTable HandleFirstArgWildcard() override;
  ResultTable HandleFirstArgVariable() override;

  bool IsAnyMatch();
  bool IsPartialMatch();
  std::shared_ptr<Result> HandlePartialMatch(const std::shared_ptr<Result>& r) override;
  std::shared_ptr<Result> HandleExactMatch(const std::shared_ptr<Result>& r) override;
};
