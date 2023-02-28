#pragma once
#include "WithClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"


bool WithClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(first_arg_);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(second_arg_);

  //The only case where 2 attr-refs are in a Boolean constraint is when they mismatch e.g. v.varName = s.stmt#
  if (is_first_arg_an_attr_ref && is_second_arg_an_attr_ref) {
    return false;
  } else {
    //with "5"=""v"", with ""v""="5", with "5"="6", with ""v""=""y""
    return first_arg_ == second_arg_;
  }
}


std::shared_ptr<Result> WithClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

