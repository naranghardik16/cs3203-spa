#pragma once

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"

class IfPatternClauseEvaluator : public ClauseEvaluator {
 private:
  std::string syn_if_;
  std::string first_arg_;
  std::string second_arg_;
  std::string third_arg_;
 public:
  IfPatternClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
      syn_if_ = syntax_pair.first;
      first_arg_ =  syntax_pair.second[0];
      second_arg_ = syntax_pair.second[1];
      third_arg_ = syntax_pair.second[2];
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) override;
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) override;
};
