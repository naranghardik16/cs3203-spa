#pragma once
#include "WithClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"


bool WithClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  return true;
}


std::shared_ptr<Result> WithClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header;
  ResultTable table;
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

