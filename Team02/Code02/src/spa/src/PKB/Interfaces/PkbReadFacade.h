#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"

/**
 * Facade implementation consisting of Read only methods
 * which acts as an interface between QPS and PKB
 */
class PkbReadFacade {
 private:
  PKB& pkb;

 public:
  PkbReadFacade(PKB& pkb);

  ~PkbReadFacade();

  /**
   * Gets variables stored in PKB
   *
   * @return set of variables
   */
  std::unordered_set<std::string> GetVariables();

  /**
   * Get constants stored in PKB
   *
   * @return set of constants
   */
  std::unordered_set<std::string> GetConstants();

  /**
   * Gets procedures stored in PKB
   *
   * @return set of procedures
   */
  std::unordered_set<std::string> GetProcedures();

  /**
   * Gets statements stored in PKB
   *
   * @return set of statements
   */
  std::unordered_set<std::string> GetStatements();

  /**
   * Gets Read statements stored in PKB
   *
   * @return set of read statements
   */
  std::unordered_set<std::string> GetReadStatements();

  /**
   * Gets Print statements stored in PKB
   *
   * @return set of print statements
   */
  std::unordered_set<std::string> GetPrintStatements();

  /**
   * Gets Call statements stored in PKB
   *
   * @return set of call statements
   */
  std::unordered_set<std::string> GetCallStatements();

  /**
   * Gets while statements stored in PKB
   *
   * @return set of while statements
   */
  std::unordered_set<std::string> GetWhileStatements();

  /**
   * Gets if statements stored in PKB
   *
   * @return set of if statements
   */
  std::unordered_set<std::string> GetIfStatements();

  /**
   * Gets assign statements stored in PKB
   *
   * @return set of assign statements
   */
  std::unordered_set<std::string> GetAssignStatements();

  std::vector<std::vector<std::string>> GetVariablesModifiedByStatement(std::string statement_number);

  //! API for Modifies
  //TODO return the Result class instead
  std::vector<std::vector<std::string>> GetModifiesStatementVariablePairs(std::string statement_type);
  std::vector<std::vector<std::string>> GetModifiesProcedureVariablePairs(bool is_call);
  std::vector<std::vector<std::string>> GetVariablesModifiedByProcedure(std::string proc_name);
  std::vector<std::vector<std::string>> GetStatementsModifiesVariable(std::string var_name, std::string statement_type);
  std::vector<std::vector<std::string>> GetProceduresModifiesVariable(std::string var_name, bool is_call);
  bool IsModifiesStatement(std::string stmt_num, std::string ident);
  bool IsModifiesProcedure(std::string proc_name, std::string ident);

  //!API for Follows
  std::vector<std::vector<std::string>> GetFollowPairs(std::string statement_type, std::string statement_type_followee);
  std::vector<std::vector<std::string>> GetStatementsFollowedBy(std::string stmt_reference, std::string statement_type);
  std::vector<std::vector<std::string>> GetStatementsFollowing(std::string stmt_reference, std::string statement_type);
  bool IsFollows(std::string stmt_reference, std::string stmt_reference_followee);


};

