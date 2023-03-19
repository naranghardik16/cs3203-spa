#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Evaluator/DesignEntityGetter.h"
#include <algorithm>

class WithClauseEvaluator : public ClauseEvaluator {
 private:
  std::string first_arg_;
  std::string second_arg_;
 public:
  WithClauseEvaluator(Map d, SyntaxPair syntax_pair) : ClauseEvaluator(d) {
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
  }
  std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) override;
  bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) override;
  Synonym ProcessArgumentForEvaluation(Synonym syn, Map &declaration_map);
};
