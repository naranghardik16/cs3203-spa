#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"
#include "CFGStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

/**
 * @class NextStore
 * Class representing the Next Store in the PKB.
 */
class NextStore {
 public:
  /**
   * Constructor for Next store.
   */
  NextStore();

  /**
   * Destructor for Next store.
   */
  ~NextStore();

  /**
   * Sets the mapping of procedure name to its corresponding control flow graph root node in the PKB.
   *
   * @param ptonode - The mapping of procedure name to its corresponding control flow graph root node.
   */
  void setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> ptonode);

  /**
   * Sets the mapping of statement number to its corresponding control flow graph root node in the PKB.
   *
   * @param stonode - The mapping of statement number to its corresponding control flow graph root node.
   */
  void setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                          std::shared_ptr<CfgNode>> stonode);

  /**
   * Extracts all the Next relations between the statements in the control flow graph.
   */
  void extractNextRelations();

  /**
   * Returns true if there exists a Next relation between the given statement numbers.
   *
   * @param statement_number - The statement number of the statement in the PKB.
   * @param next_statement_number - The statement number of the next statement in the PKB.
   * @return True if there exists a Next relation between the given statement numbers.
   */
  bool hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                       PkbTypes::STATEMENT_NUMBER next_statement_number);

  /**
   * Returns true if there exists any Next relation in the PKB.
   * @return True if there exists any Next relation in the PKB.
   */
  bool hasAnyNextRelation();

  /**
   * Retrieves all pairs of statements having Next relation
   * @return set of pair of statements satisfying Next relation
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextPairs();

  /**
   * Returns all the pairs of statement numbers that have a Next relation between them in the PKB.
   * @param statement_number
   * @return A set of all pairs of statement numbers that have a Next relation between them in the PKB.
   */
  bool hasNext(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Returns true if there exists any statement number that has a Next relation from the given statement number.
   * @param statement_number - The statement number of the statement in the PKB.
   * @return True if there exists any statement number that has a Next relation from the given statement number.
   */
  bool hasNextBy(PkbTypes::STATEMENT_NUMBER statement_number);

//  bool hasNextStarRelation(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::STATEMENT_NUMBER next_statement_number);
//
//  bool hasAnyNextStarRelation();
//
//  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
//  retrieveAllNextStarPairs();

 private:
  // A many-to-many store for PkbTypes::STATEMENT_NUMBER pairs representing Next relations between statements.
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> next_store_;

  // A map from statement numbers to their corresponding CfgNode objects.
  std::unordered_map<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<CfgNode>> statement_number_to_cfg_node_map_;

  // A map from procedure names to their corresponding CfgNode objects.
  std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> procedure_name_to_cfg_node_map_;
};

