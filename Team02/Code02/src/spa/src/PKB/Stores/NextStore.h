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
   * Sets the procedure name to its cfg root node mapping(s) in Next store.
   *
   * @param ptonode - A map that contains procedure name to its root cfg node mapping.
   */
  void setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> ptonode);

  /**
   * Sets the statement number to its cfg root node mapping(s) in Next store.
   *
   * @param stonode - A map that contains statement number to its root cfg node mapping.
   */
  void setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                          std::shared_ptr<CfgNode>> stonode);

  /**
   * Extracts all the Next relations between the statements.
   */
  void extractNextRelations();

  /**
   * Checks if there exists a Next relation between the given statement numbers.
   *
   * @param statement_number - The statement number that appears first.
   * @param next_statement_number - The statement number of that appears next.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                       PkbTypes::STATEMENT_NUMBER next_statement_number);

  /**
   * Checks if there exists any Next relation in the store.
   *
   * @return True if any relation exists, false otherwise.
   */
  bool hasAnyNextRelation();

  /**
   * Retrieves all pairs of statements having Next relation.
   *
   * @return A set of pair of statements satisfying Next relation.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextPairs();

  /**
   * Checks if a particular statement has a next relation with another statement.
   *
   * @param statement_number - The statement that should appear first.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNext(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Checks if a particular statement has a next relation with another statement.
   *
   * @param statement_number - The statement that should appear second ie next with respect to some other statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNextBy(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all pairs of statements that have Next star relation.
   *
   * @return A set of pairs of statements satisfying the Next star relation.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextStarPairs();

  /**
   * Checks if there is a Next star relation between the given statements.
   *
   * @param statement_number - The statement that should appear first.
   * @param next_statement_number - The statement that should appear second ie next with respect to the first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNextStarRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                           PkbTypes::STATEMENT_NUMBER next_statement_number);

  /**
   * Checks if there is a Next star relation with given statement appearing first.
   *
   * @param statement_number - The statement that should appear first.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNextStar(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Checks if there is a Next star relation with given statement appearing second.
   *
   * @param statement_number - The statement that should appear second ie Next star with respect
   *                           to some other statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasNextStarBy(PkbTypes::STATEMENT_NUMBER statement_number);

 private:
  // A many-to-many store for PkbTypes::STATEMENT_NUMBER pairs representing Next relations between statements.
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> next_store_;

  // A map from statement numbers to their corresponding CfgNode objects.
  std::unordered_map<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<CfgNode>> statement_number_to_cfg_node_map_;

  // A map from procedure names to their corresponding CfgNode objects.
  std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> procedure_name_to_cfg_node_map_;
};

