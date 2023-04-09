#pragma once

#include <utility>

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"

class ExpressionSpecEvaluator {
 public:
  virtual std::shared_ptr<Result> HandlePartialMatch(const std::shared_ptr<Result>& r) = 0;
  virtual std::shared_ptr<Result> HandleExactMatch(const std::shared_ptr<Result>& r) = 0;
};
