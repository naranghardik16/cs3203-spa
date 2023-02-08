#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include "General/StatementTypeEnum.h"
#include <memory>
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

class ClauseEvaluator {
 private:
  Map declaration_map_;

 public:
  ClauseEvaluator(Map declaration_map) {
    declaration_map_ = declaration_map;
  }

  Map GetDeclarationMap();
  virtual std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) = 0;
  virtual bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) = 0;
  virtual ~ClauseEvaluator() {};
};
