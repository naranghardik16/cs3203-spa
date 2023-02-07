#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "General/StatementTypeEnum.h"

//! A temp hash function used to hash a pair of any kind
struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2>& p) const
  {
    auto hash_1 = std::hash<T1>{}(p.first);
    auto hash_2 = std::hash<T2>{}(p.second);

    if (hash_1 != hash_2) {
      return hash_1 ^ hash_2;
    }

    // If hash1 == hash2, their XOR is zero.
    return hash_1;
  }
};

typedef std::string SingleConstraint;
//! E.g. {1,2,3,4} for Select a (assign) is a SingleConstraintSet
typedef std::unordered_set<SingleConstraint> SingleConstraintSet;

typedef std::pair<std::string, std::string> PairConstraint;
//! E.g. Uses(s,v) gives a PairConstraintSet {(1,v1), (2,v2)}
typedef std::unordered_set<PairConstraint, hash_pair> PairConstraintSet;


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

  //! API for Modifies - Statement

  /**
 * Get variables modified by a specific statement number
 * @param statement_number which is the statement number in string
 * @return a set of variable names
 */
  std::unordered_set<std::string> GetVariablesModifiedByStatement(std::string statement_number);

  /**
   * Returns (statement number, variable name) pairs that have a Modifies relationship with the statement numbers
   * being constrained to the statement_type specified
   * @param statement_type enum
   * @return a set of pairs (statement number, variable name)
   */
  PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);

  /**
 * Get statements that modify a specific variable, with the statements being constrained to a type specification
 * @param var_name which is the name of the variable like "v"
 * @param statement_type which is a constraint to filter the statements returned
 * @return a set of variable names
 */
  std::unordered_set<std::string> GetStatementsModifiesVariable(std::string var_name, StatementType statement_type);


  /**
  * Returns the statement numbers of a statement type that have a Modifies relationship
  * @param stmt_type which is the statement type constraint
  * @return a set of statement numbers
  */
  std::unordered_set<std::string> GetModifiers(StatementType stmt_type);

  /**
  * Check if a specific statement and variable have a Modifies relationship
  * @param stmt_num which is the statement number
  * @param var_name which is the name of the variable like "v"
  * @return a set of variable names
  */
  bool IsModifiesStatement(std::string stmt_num, std::string var_name);


  /*
  bool HasModifiesRelationship(StatementType stmt_type);

  //! API for Modifies - Procedure
  std::unordered_set<std::pair<std::string,std::string>> GetModifiesProcedureVariablePairs(bool is_call);
  std::unordered_set<std::string> GetVariablesModifiedByProcedure(std::string proc_name);
  std::unordered_set<std::string> GetProceduresModifiesVariable(std::string var_name, bool is_call);
  bool IsModifiesProcedure(std::string proc_name, std::string ident);

  //!API for Follows
  std::unordered_set<std::pair<std::string,std::string>> GetFollowPairs(std::string statement_type, std::string statement_type_followee);
  std::unordered_set<std::string> GetStatementsFollowedBy(std::string stmt_reference, std::string statement_type);
  std::unordered_set<std::string> GetStatementsFollowing(std::string stmt_reference, std::string statement_type);
  bool IsFollows(std::string stmt_reference, std::string stmt_reference_followee);
*/
};

