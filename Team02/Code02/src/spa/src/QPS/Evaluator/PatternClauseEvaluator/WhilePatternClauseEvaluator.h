#pragma once

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"

class WhilePatternClauseEvaluator : public ClauseEvaluator {
 private:
  std::string syn_while_;
  std::string first_arg_;
  std::string second_arg_;
 public:
  WhilePatternClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
      syn_while_ = syntax_pair.first;
      first_arg_ =  syntax_pair.second[0];
      second_arg_ = syntax_pair.second[1];
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) override;
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) override;
};
