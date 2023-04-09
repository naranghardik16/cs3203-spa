#pragma once

#include <utility>

#include "QPS/Evaluator/PatternClauseEvaluator/PatternClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "General/LexicalRuleValidator.h"

class IfPatternClauseEvaluator : public PatternClauseEvaluator {

 public:
  IfPatternClauseEvaluator(Map d,
                           SyntaxPair syntax_pair,
                           std::shared_ptr<PkbReadFacade> pkb
                           ) : PatternClauseEvaluator(std::move(d), std::move(syntax_pair),
                                                      std::move(pkb)) {
  }

  ResultTable HandleFirstArgSyn() override;
  ResultTable HandleFirstArgWildcard() override;
  ResultTable HandleFirstArgVariable() override;
};
