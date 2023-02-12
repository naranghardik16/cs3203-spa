#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include "General/StatementTypeEnum.h"
#include <memory>
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

/**
 * Created by factory pattern from ClauseSyntax and is used to evaluate subclauses individually
 */
class ClauseEvaluator {
 private:
  Map declaration_map_;

 public:
  ClauseEvaluator(Map declaration_map) {
    declaration_map_ = declaration_map;
  }

  /**
   * A getter function to get the map containing informations on declarations made
   * @return an unordered map of synonyms as key and corresponding design entity as the value
   */
  Map GetDeclarationMap();

  /**
   * Evaluates non-boolean constraints by interacting with PKB
   * @param pkb which stores data about information from the SIMPLE program
   * @return a Result class containing information about the evaluation for further handling
   */
  virtual std::shared_ptr<Result> EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) = 0;

  /**
   * Evaluates a boolean constraint by interacting with PKB
   * @param pkb which stores data about information from the SIMPLE program
   * @return true if the boolean constraint is fulfilled, else false which means final evaluation of the query is None
   */
  virtual bool EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) = 0;

  virtual ~ClauseEvaluator() {};
};
