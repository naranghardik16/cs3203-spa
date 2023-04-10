#pragma once

#include <utility>

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"

class PatternClauseEvaluator : public ClauseEvaluator {
 protected:
  std::string syn_;
  std::string first_arg_;
  std::string second_arg_;

 public:
  PatternClauseEvaluator(Map d, SyntaxPair syntax_pair, std::shared_ptr<PkbReadFacade> pkb) :
                         ClauseEvaluator(std::move(d), std::move(pkb)) {
    syn_ = syntax_pair.first;
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
  }

  bool EvaluateBooleanConstraint() override;
  virtual std::shared_ptr<Result> EvaluateClause();

  virtual ResultTable HandleFirstArgSyn() = 0;
  virtual ResultTable HandleFirstArgWildcard() = 0;
  virtual ResultTable HandleFirstArgVariable() = 0;
};
