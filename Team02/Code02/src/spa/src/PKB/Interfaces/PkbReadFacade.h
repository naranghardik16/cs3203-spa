#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "General/StatementTypeEnum.h"

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
  PkbCommunicationTypes::SingleConstraintSet GetVariables();

  /**
   * Get constants stored in PKB
   *
   * @return set of constants
   */
  PkbCommunicationTypes::SingleConstraintSet GetConstants();

  /**
   * Gets procedures stored in PKB
   *
   * @return set of procedures
   */
  PkbCommunicationTypes::SingleConstraintSet GetProcedures();

  /**
   * Gets statements stored in PKB
   *
   * @return set of statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatements();

  /**
   * Gets Read statements stored in PKB
   *
   * @return set of read statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetReadStatements();

  /**
   * Gets Print statements stored in PKB
   *
   * @return set of print statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetPrintStatements();

  /**
   * Gets Call statements stored in PKB
   *
   * @return set of call statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetCallStatements();

  /**
   * Gets while statements stored in PKB
   *
   * @return set of while statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetWhileStatements();

  /**
   * Gets if statements stored in PKB
   *
   * @return set of if statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetIfStatements();

  /**
   * Gets assign statements stored in PKB
   *
   * @return set of assign statements
   */
  PkbCommunicationTypes::SingleConstraintSet GetAssignStatements();

  //! API for Modifies - Statement

  /**
 * Get variables modified by a specific statement number
 * @param statement_number which is the statement number in string
 * @return a set of variable names
 */
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);

  /**
   * Returns (statement number, variable name) pairs that have a Modifies relationship with the statement numbers
   * being constrained to the statement_type specified
   * @param statement_type enum
   * @return a set of pairs (statement number, variable name)
   */
  PkbCommunicationTypes::PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);

  /**
 * Get statements that modify a specific variable, with the statements being constrained to a type specification
 * @param var_name which is the name of the variable like "v"
 * @param statement_type which is a constraint to filter the statements returned
 * @return a set of variable names
 */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type);


  /**
  * Returns the statement numbers of a statement type that have a Modifies relationship
  * @param stmt_type which is the statement type constraint
  * @return a set of statement numbers
  */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatModify(StatementType stmt_type);

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
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name);

  /**
   * Returns (procedure_name, variable name) pairs that have a Modifies relationship with the statement numbers
   * @return a set of pairs (procedure_name, variable name)
   */
  PkbCommunicationTypes::PairConstraintSet GetModifiesProcedureVariablePairs();

  /**
 * Get procedures that modify a specific variable
 * @param var_name which is the name of the variable like "v"
 * @return a set of variable names
 */
  PkbCommunicationTypes::SingleConstraintSet GetProceduresModifiesVariable(std::string var_name);


  /**
  * Returns the procedure names of procedures that have a Modifies relationship
  * @return a set of procedure names
  */
  PkbCommunicationTypes::SingleConstraintSet GetProceduresThatModify();

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
  PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);


  /**
 * Returns the statement numbers of statements followed by a specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowedBy(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements following a specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowing(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements with followers
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are followers
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);

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

  //!API for Parent

  /**
   * Returns (statement number, statement number) pairs that have a Parent-Child Relationship
   * with the 2nd statement number being the child of the first
   * @param statement_type is the statement type of the statement that is the parent
   * @param statement_type_child is the statement type of the child
   * @return a set of pairs (statement number, statement number)
   */
  PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child);


  /**
 * Returns the statement numbers of statements that are parent of the specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are child of the specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are parents
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are child of another statements
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type);

  /**
   * Returns true if the statement in the first argument is the parent of the statement in the second argument
   * @param statement_num statement num of a statement
   * @param statement_num_child is the statement that is child of the statement in the first argument
   * @return bool
   */
  bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child);

  /**
 * Returns true if there is a Parent relationship stored between any statements
 * @return bool
 */
  bool IsAnyParentRelationshipPresent();


  //!API for ParentStar

  /**
   * Returns (statement number, statement number) pairs that have a Ancestor-Descendant Relationship
   * with the 2nd statement number being the child of the first
   * @param statement_type is the statement type of the statement that is the parent
   * @param statement_type_descendant is the statement type of the child
   * @return a set of pairs (statement number, statement number)
   */
  PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant);


  /**
 * Returns the statement numbers of statements that are ancestors of the specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are descendants of the specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num,
                                                                               StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are ancestors of any other statement type
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are descendants of another statement (any type)
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type);

  /**
   * Returns true if the statement in the first argument is the ancestor of the statement in the second argument
   * @param statement_num statement num of a statement
   * @param statement_num_descendant is the statement that should is descendant of the statement in the first argument
   * @return bool
   */
  bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant);

  /**
 * Returns true if there is a Parent relationship stored between any statements
 * @return bool
 */
  bool IsAnyAncestorDescendantRelationshipPresent();
};

