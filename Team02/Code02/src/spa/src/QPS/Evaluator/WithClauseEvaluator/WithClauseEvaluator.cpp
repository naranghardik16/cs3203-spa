#pragma once
#include "WithClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"


bool WithClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(first_arg_);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(second_arg_);

  if (is_first_arg_an_attr_ref && is_second_arg_an_attr_ref) {
    //e.g. p.procName = a.stmt#
    return false;
  } else if(is_first_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return false;
  } else if (is_second_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return false;
  } else {
    //e.g. 5=5, v=6, 6=v
    return first_arg_ == second_arg_;
  }
}


std::shared_ptr<Result> WithClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

