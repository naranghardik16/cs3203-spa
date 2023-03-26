#pragma once
#include "QPS/Util/QPSTypeDefs.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/Result.h"
#include "General/StatementTypeEnum.h"
#include <memory>
#include <utility>
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

/**
 * Created by factory pattern from ClauseSyntax and is used to evaluate subclauses individually
 */
class ClauseEvaluator {
 protected:
  Map declaration_map_;
  std::shared_ptr<PkbReadFacade> pkb_;

 public:
  ClauseEvaluator(Map declaration_map, std::shared_ptr<PkbReadFacade> pkb) {
    declaration_map_ = std::move(declaration_map);
    pkb_ = std::move(pkb);
  }

  /**
   * A getter function to get the map containing informations on declarations made
   * @return an unordered map of synonyms as key and corresponding design entity as the value
   */
  Map GetDeclarationMap();

  /**
 * Converts an unordered set of strings (Pkb output) to a ResultRow format for QPS to handle interdependent clauses in PQL queries
 * @param s which is an unordered set of strings
 * @return the unordered set in ResultTable format
 */
  static ResultTable ConvertSetToResultTableFormat(const PkbCommunicationTypes::SingleConstraintSet& s);

  /**
   * Converts an unordered set of pairs (Pkb output) to a ResultRow format for QPS to handle interdependent clauses in PQL queries
   * @param s which is an unordered set of pairs
   * @return  the unordered set in ResultTable format
   */
  static ResultTable ConvertPairSetToResultTableFormat(const PkbCommunicationTypes::PairConstraintSet& s);

  /**
   * Filter the set when the two synonyms of clause are same.
   *
   * @param s
   * @return the filtered unordered set
   */
  static PkbCommunicationTypes::PairConstraintSet FilterForSameSynonym(const PkbCommunicationTypes::PairConstraintSet& s);

  /**
   * Evaluates non-boolean constraints by interacting with Pkb
   * @param pkb which stores data about information from the SIMPLE program
   * @return a Result class containing information about the evaluation for further handling
   */
  virtual std::shared_ptr<Result> EvaluateClause() = 0;

  /**
   * Evaluates a boolean constraint by interacting with Pkb
   * @param pkb which stores data about information from the SIMPLE program
   * @return true if the boolean constraint is fulfilled, else false which means final evaluation of the query is None
   */
  virtual bool EvaluateBooleanConstraint() = 0;

  virtual ~ClauseEvaluator() {};
};
