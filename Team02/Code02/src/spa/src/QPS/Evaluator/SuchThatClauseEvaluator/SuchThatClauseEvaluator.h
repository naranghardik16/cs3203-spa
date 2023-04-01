#pragma once

#include <utility>

#include "QPS/Evaluator/ClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"

class SuchThatClauseEvaluator : public ClauseEvaluator {
 protected:
  std::string relationship_reference_;
  std::string first_arg_;
  std::string second_arg_;
  StatementType arg_1_type_;
  StatementType arg_2_type_;

 public:
  SuchThatClauseEvaluator(Map d,
                          SyntaxPair syntax_pair,
                          std::shared_ptr<PkbReadFacade> pkb
                          ) : ClauseEvaluator(std::move(d), std::move(pkb)) {
      relationship_reference_ = syntax_pair.first;
      first_arg_ =  syntax_pair.second[0];
      second_arg_ = syntax_pair.second[1];
      arg_1_type_ = QueryUtil::GetStatementType(declaration_map_, first_arg_);
      arg_2_type_ = QueryUtil::GetStatementType(declaration_map_, second_arg_);
  }

  bool EvaluateBooleanConstraint() override;
  std::shared_ptr<Result> EvaluateClause() override;

  virtual bool CheckIfReturnEmpty();
  virtual bool HandleBothWildcard() = 0;
  virtual bool HandleFirstWildcardSecondValue() = 0;
  virtual bool HandleFirstValueSecondWildcard() = 0;
  virtual bool HandleBothValue() = 0;
  virtual ResultTable HandleBothSynonym() = 0;
  virtual ResultTable HandleFirstSynonymSecondWildcard() = 0;
  virtual ResultTable HandleFirstSynonymSecondValue() = 0;
  virtual ResultTable HandleFirstWildcardSecondSynonym() = 0;
  virtual ResultTable HandleFirstValueSecondSynonym() = 0;
};
