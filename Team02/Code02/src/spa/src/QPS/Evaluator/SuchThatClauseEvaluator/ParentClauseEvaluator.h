#pragma once

#include "QPS/Evaluator/SuchThatClauseEvaluator/SuchThatClauseEvaluator.h"
#include "PKB/Types/PkbCommunicationTypes.h"

class ParentClauseEvaluator : public SuchThatClauseEvaluator {
 private:
  bool is_first_arg_a_container_syn_;
  bool is_same_syn_or_value_pairs_;

 public:
  ParentClauseEvaluator(Map d,
                        SyntaxPair syntax_pair,
                        std::shared_ptr<PkbReadFacade> pkb
                        ) : SuchThatClauseEvaluator(std::move(d), std::move(syntax_pair), std::move(pkb)) {
    is_first_arg_a_container_syn_ = QueryUtil::IsIfSynonym(declaration_map_, first_arg_)
        || QueryUtil::IsWhileSynonym(declaration_map_, first_arg_)
        || QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
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
