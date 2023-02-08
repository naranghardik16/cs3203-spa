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
  SingleConstraintSet GetVariables();

  /**
   * Get constants stored in PKB
   *
   * @return set of constants
   */
  SingleConstraintSet GetConstants();

  /**
   * Gets procedures stored in PKB
   *
   * @return set of procedures
   */
  SingleConstraintSet GetProcedures();

  /**
   * Gets statements stored in PKB
   *
   * @return set of statements
   */
  SingleConstraintSet GetStatements();

  /**
   * Gets Read statements stored in PKB
   *
   * @return set of read statements
   */
  SingleConstraintSet GetReadStatements();

  /**
   * Gets Print statements stored in PKB
   *
   * @return set of print statements
   */
  SingleConstraintSet GetPrintStatements();

  /**
   * Gets Call statements stored in PKB
   *
   * @return set of call statements
   */
  SingleConstraintSet GetCallStatements();

  /**
   * Gets while statements stored in PKB
   *
   * @return set of while statements
   */
  SingleConstraintSet GetWhileStatements();

  /**
   * Gets if statements stored in PKB
   *
   * @return set of if statements
   */
  SingleConstraintSet GetIfStatements();

  /**
   * Gets assign statements stored in PKB
   *
   * @return set of assign statements
   */
  SingleConstraintSet GetAssignStatements();

  //! API for Modifies - Statement

  /**
 * Get variables modified by a specific statement number
 * @param statement_number which is the statement number in string
 * @return a set of variable names
 */
  SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);

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
  SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type);


  /**
  * Returns the statement numbers of a statement type that have a Modifies relationship
  * @param stmt_type which is the statement type constraint
  * @return a set of statement numbers
  */
  SingleConstraintSet GetStatementsThatModify(StatementType stmt_type);

  /**
  * Check if a specific statement and variable have a Modifies relationship
  * @param stmt_num which is the statement number
  * @param var_name which is the name of the variable like "v"
  * @return a set of variable names
  */
  bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name);

  //! API for Modifies - Procedure

  /**
 * Get variables modified by a specific procedure
 * @param procedure_name which is the name of the procedure
 * @return a set of variable names
 */
  SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name);

  /**
   * Returns (procedure_name, variable name) pairs that have a Modifies relationship with the statement numbers
   * @param is_call  If is_call is True, then we only want procedures that are called in call statements
   * @return a set of pairs (procedure_name, variable name)
   */
  PairConstraintSet GetModifiesProcedureVariablePairs(bool is_call);

  /**
 * Get procedures that modify a specific variable
 * @param var_name which is the name of the variable like "v"
 * @param is_call  If is_call is True, then we only want procedures that are called in call statements
 * @return a set of variable names
 */
  SingleConstraintSet GetProceduresModifiesVariable(std::string var_name, bool is_call);


  /**
  * Returns the procedure names of procedures that have a Modifies relationship
  * @param is_call  If is_call is True, then we only want procedures that are called in call statements
  * @return a set of procedure names
  */
  SingleConstraintSet GetProceduresThatModify(bool is_call);

  /**
  * Check if a specific procedure and variable have a Modifies relationship
  * @param procedure_name which is the name of the procedure
  * @param var_name which is the name of the variable like "v"
  * @return true if the procedure and variable have a Modifies relationship
  */
  bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name);

  //!API for Follows

  /**
   * Returns (statement number, statement number) pairs that have a Follows Relationship
   * with the 2nd statement number being the follower of the first
   * @param statement_type is the statement type of the statement being followed
   * @param statement_type_follower is the statement type of the follower
   * @return a set of pairs (statement number, statement number)
   */
  PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);


  /**
 * Returns the statement numbers of statements followed by a specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  SingleConstraintSet GetStatementsFollowedBy(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements following a specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  SingleConstraintSet GetStatementsFollowing(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements with followers
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are followers
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);

  /**
   * Returns true if the statement in the second argument follows the statement in the first argument
   * @param statement_num statement num of a statement
   * @param statement_num_follower is the statement that should follow the statement in the first argument
   * @return bool
   */
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower);

  /**
 * Returns true if there is a follows relationship stored between any statements
 * @return bool
 */
  bool IsAnyFollowsRelationshipPresent();

};

