#pragma once

#include "QPS/Evaluator/SuchThatClauseEvaluator/SuchThatClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"

class AffectsStarClauseEvaluator : public SuchThatClauseEvaluator {
 private:
  bool is_same_syn_or_value_pairs_;

 public:
  AffectsStarClauseEvaluator(Map d,
                             SyntaxPair syntax_pair,
                             std::shared_ptr<PkbReadFacade> pkb
                             ) : SuchThatClauseEvaluator(std::move(d), std::move(syntax_pair), std::move(pkb)) {
    is_same_syn_or_value_pairs_ = first_arg_ == second_arg_;
  }

  bool CheckIfReturnEmpty() override;
  bool HandleBothWildcard() override;
  bool HandleFirstWildcardSecondValue() override;
  bool HandleFirstValueSecondWildcard() override;
  bool HandleBothValue() override;
  ResultTable HandleBothSynonym() override;
  ResultTable HandleFirstSynonymSecondWildcard() override;
  ResultTable HandleFirstSynonymSecondValue() override;
  ResultTable HandleFirstWildcardSecondSynonym() override;
  ResultTable HandleFirstValueSecondSynonym() override;
};
