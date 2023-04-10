#pragma once
#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Evaluator/DesignEntityGetter.h"
#include <algorithm>
#include <utility>

class WithClauseEvaluator : public ClauseEvaluator {
 protected:
  std::string first_arg_;
  std::string second_arg_;

 public:
  WithClauseEvaluator(Map d,
                      SyntaxPair syntax_pair,
                      std::shared_ptr<PkbReadFacade> pkb
                      ) : ClauseEvaluator(std::move(d), std::move(pkb)) {
    first_arg_ =  syntax_pair.second[0];
    second_arg_ = syntax_pair.second[1];
  }

  std::shared_ptr<Result> EvaluateClause() override;
  bool EvaluateBooleanConstraint() override;
  static Synonym ProcessArgumentForEvaluation(std::string arg, Map &declaration_map);
  std::shared_ptr<Result> HandleOneAttrRefCase(const Synonym& attr_ref_syn, const ResultTable& filter_table);
};
