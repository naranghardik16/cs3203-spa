#pragma once

#include <memory>

#include "core/cfg_model/Cfg.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class CfgStore
 * Class representing the CFG Store in Pkb.
 *
 * The CfgStore class is responsible for maintaining information about the
 * control flow graph of the source program.
 *
 */
class CfgStore {
 public:
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_map<Procedure, CfgNodePtr> ProcedureToCfgNodeMap;
  typedef std::unordered_map<StatementNumber, CfgNodePtr> StatementNumberToCfgNodeMap;
  
  /**
   * Constructor for the CfgStore class.
   */
  CfgStore();

  /**
   * Destructor for the CfgStore class.
   */
  ~CfgStore();

  /**
   * Adds the control flow graph to the store.
   *
   * @param cfg - The CFG to be added.
   */
  void AddCfg(const CfgPtr& cfg);

  /**
   * Retrieves the CFG given a procedure.
   *
   * @param procedure - The procedure whose CFG is to be retrieved.
   * @return The root node of the CFG for the given procedure.
   */
  CfgNodePtr GetCfgNodeFromProcedure(const Procedure& procedure);

  /**
   * Retrieves the CFG node given a statement number.
   *
   * @param statement_number - The statement number representing the statement whose CFG node is to be retrieved.
   * @return The CFG node for the given statement number.
   */
  CfgNodePtr GetCfgNodeFromStatementNumber(const StatementNumber& statement_number);

  /**
   * Returns the CFG stored in this CfgStore.
   *
   * @return The CFG stored in this CfgStore.
   */
  [[nodiscard]] CfgPtr GetCfg() const;

  /**
   * Retrieves the map of procedure name to its respective cfg node.
   *
   * @return An unordered map that contains procedure name and cfg nodes as keys and values respectively.
   */
  ProcedureToCfgNodeMap GetProcedureToCfgNodeMap();

  /**
   * Retrieves the map of statement number to its respective cfg node.
   *
   * @return An unordered map that contains statement number and cfg nodes as keys and values respectively.
   */
  StatementNumberToCfgNodeMap GetStatementNumberToCfgNodeMap();

  /**
   * Returns the number of CFGs stored in the CfgStore
   *
   * @return The number of CFGs stored in the CfgStore
   */
  int GetCfgCount() const;

 private:
  CfgPtr cfg_;
};

