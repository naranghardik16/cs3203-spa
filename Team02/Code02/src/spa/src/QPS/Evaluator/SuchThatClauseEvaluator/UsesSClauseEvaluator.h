#pragma once

#include "QPS/Evaluator/SuchThatClauseEvaluator/SuchThatClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"

class UsesSClauseEvaluator : public SuchThatClauseEvaluator {
 private:
  bool is_first_arg_a_read_synonym_;

 public:
  UsesSClauseEvaluator(Map d,
                       SyntaxPair syntax_pair,
                       std::shared_ptr<PkbReadFacade> pkb
                      ) : SuchThatClauseEvaluator(std::move(d), std::move(syntax_pair), std::move(pkb)) {
    is_first_arg_a_read_synonym_ = QueryUtil::IsReadSynonym(declaration_map_, first_arg_);
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
