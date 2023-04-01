#pragma once

#include "QPS/Evaluator/SuchThatClauseEvaluator/SuchThatClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"

class AffectsClauseEvaluator : public SuchThatClauseEvaluator {
 private:
  bool is_first_arg_a_valid_syn_;
  bool is_second_arg_a_valid_syn_;
  bool is_same_syn_or_value_pairs_;

 public:
  AffectsClauseEvaluator(Map d,
                         SyntaxPair syntax_pair,
                         std::shared_ptr<PkbReadFacade> pkb
                         ) : SuchThatClauseEvaluator(std::move(d), std::move(syntax_pair), std::move(pkb)) {
    is_first_arg_a_valid_syn_ = QueryUtil::IsAssignSynonym(declaration_map_, first_arg_)
        || QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
    is_second_arg_a_valid_syn_ = QueryUtil::IsAssignSynonym(declaration_map_, second_arg_)
        || QueryUtil::IsStatementSynonym(declaration_map_, second_arg_);
    is_same_syn_or_value_pairs_ = first_arg_ == second_arg_;
  }

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
