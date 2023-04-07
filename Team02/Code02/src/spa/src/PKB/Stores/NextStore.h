#pragma once

#include <stack>

#include "CfgStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"
#include "PKB/Util/TransitiveRelationUtil.h"

/**
 * @class NextStore
 * Class representing the Next Store in the Pkb.
 */
class NextStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::stack<StatementNumber> StatementNumberStack;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;
  typedef std::unordered_map<Procedure, CfgNodePtr> ProcedureToCfgNodeMap;
  typedef std::unordered_map<StatementNumber, CfgNodePtr> StatementToCfgNodeMap;
  typedef std::unordered_set<std::pair<StatementNumber, StatementNumber>, PairHasherUtil::hash_pair>
      StatementStatementPairSet;
  typedef ManyToManyStore<StatementNumber, StatementNumber> MultiStatementToStatementStore;
  typedef std::stack<std::pair<int, CfgNodePtr>> StatementCfgNodePtrStack;

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
  void SetProcedureToCfgNodeMap(const ProcedureToCfgNodeMap &ptonode);

  /**
   * Sets the statement number to its cfg root node mapping(s) in Next store.
   *
   * @param stonode - A map that contains statement number to its root cfg node mapping.
   */
  void SetStatementNumberToCfgNodeMap(const StatementToCfgNodeMap &stonode);

  /**
   * Extracts all the Next relations between the statements.
   */
  void AddNextRelations();

  /**
   * Checks if there exists a Next relation between the given statement numbers.
   *
   * @param statement_number - The statement number that appears first.
   * @param next_statement_number - The statement number of that appears next.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextRelation(const StatementNumber &statement_number, const StatementNumber &next_statement_number);

  /**
   * Checks if there exists any Next relation in the store.
   *
   * @return True if any relation exists, false otherwise.
   */
  bool HasNextRelation();

  /**
   * Retrieves all pairs of statements having Next relation.
   *
   * @return A set of pair of statements satisfying Next relation.
   */
  StatementStatementPairSet GetNextPairs();

  /**
   * Checks if a particular statement has a next relation with another statement.
   *
   * @param statement_number - The statement that should appear first.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextRelation(const StatementNumber &statement_number);

  /**
   * Checks if a particular statement has a next relation with another statement.
   *
   * @param statement_number - The statement that should appear second ie next with respect to some other statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextRelationBy(const StatementNumber &statement_number);

  /**
   * Retrieves all pairs of statements that have Next star relation.
   *
   * @return A set of pairs of statements satisfying the Next star relation.
   */
  StatementStatementPairSet GetNextStarPairs();

  /**
   * Checks if there is a Next star relation between the given statements.
   *
   * @param statement_number - The statement that should appear first.
   * @param next_statement_number - The statement that should appear second ie next with respect to the first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextStarRelation(const StatementNumber &statement_number, const StatementNumber &next_statement_number);

  /**
   * Checks if there is a Next star relation with given statement appearing first.
   *
   * @param statement_number - The statement that should appear first.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextStarRelation(const StatementNumber &statement_number);

  /**
   * Checks if there is a Next star relation with given statement appearing second.
   *
   * @param statement_number - The statement that should appear second ie Next star with respect
   *                           to some other statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasNextStarRelationBy(const StatementNumber &statement_number);

 private:
  // A many-to-many store for StatementNumber pairs representing Next relations between statements.
  MultiStatementToStatementStore next_relation_store_;

  // A map from statement numbers to their corresponding CfgNode objects.
  StatementToCfgNodeMap statement_number_to_cfg_node_map_;

  // A map from procedure names to their corresponding CfgNode objects.
  ProcedureToCfgNodeMap procedure_name_to_cfg_node_map_;
};

