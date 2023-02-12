#pragma once

#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "General/StatementTypeEnum.h"

/**
 * Facade implementation consisting of read-only methods
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
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariables();

  /**
   * Get constants stored in PKB
   *
   * @return set of constants
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetConstants();

  /**
   * Gets procedures stored in PKB
   *
   * @return set of procedures
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProcedures();

  /**
   * Gets statements stored in PKB
   *
   * @return set of statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatements();

  /**
   * Gets Read statements stored in PKB
   *
   * @return set of read statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetReadStatements();

  /**
   * Gets Print statements stored in PKB
   *
   * @return set of print statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetPrintStatements();

  /**
   * Gets Call statements stored in PKB
   *
   * @return set of call statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetCallStatements();

  /**
   * Gets while statements stored in PKB
   *
   * @return set of while statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetWhileStatements();

  /**
   * Gets if statements stored in PKB
   *
   * @return set of if statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetIfStatements();

  /**
   * Gets assign statements stored in PKB
   *
   * @return set of assign statements
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignStatements();

  //! API for Modifies - Statement

  /**
 * Get variables modified by a specific statement number
 * @param statement_number which is the statement number in string
 * @return a set of variable names
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);

  /**
   * Returns (statement number, variable name) pairs that have a Modifies relationship with the statement numbers
   * being constrained to the statement_type specified
   * @param statement_type enum
   * @return a set of pairs (statement number, variable name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);

  /**
 * Get statements that modify a specific variable, with the statements being constrained to a type specification
 * @param var_name which is the name of the variable like "v"
 * @param statement_type which is a constraint to filter the statements returned
 * @return a set of variable names
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsModifiesVariable(std::string variable, StatementType statement_type);


  /**
  * Returns the statement numbers of a statement type that have a Modifies relationship
  * @param stmt_type which is the statement type constraint
  * @return a set of statement numbers
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatModify(StatementType stmt_type);

  /**
  * Check if a specific statement and variable have a Modifies relationship
  * @param stmt_num which is the statement number
  * @param var_name which is the name of the variable like "v"
  * @return a set of variable names
  */
  virtual bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name);

  //! API for Modifies - Procedure

  /**
 * Get variables modified by a specific procedure
 * @param procedure_name which is the name of the procedure
 * @return a set of variable names
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name);

  /**
   * Returns (procedure_name, variable name) pairs that have a Modifies relationship with the statement numbers
   * @return a set of pairs (procedure_name, variable name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetModifiesProcedureVariablePairs();

  /**
 * Get procedures that modify a specific variable
 * @param var_name which is the name of the variable like "v"
 * @return a set of variable names
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresModifiesVariable(std::string var_name);


  /**
  * Returns the procedure names of procedures that have a Modifies relationship
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresThatModify();

  /**
  * Check if a specific procedure and variable have a Modifies relationship
  * @param procedure_name which is the name of the procedure
  * @param var_name which is the name of the variable like "v"
  * @return true if the procedure and variable have a Modifies relationship
  */
  virtual bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name);

  //! API for Uses - Statement

  /**
   * Returns all (s, v) pairs where Uses(s, v) relationship holds and s is of given statement type.
   *
   * @param statement_type Statement type of s
   * @return a set of pairs (statement number, variable name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetStmtUsesPair(StatementType statement_type);

  /**
   * Returns all s where Uses(s, v) relationship holds and s is of given statement type.
   * i.e. return the first value of stmt Uses pairs
   *
   * @param statement_type Statement type of s
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStmtUsesFirst(StatementType statement_type);

  /**
   * Returns all v where Uses(stmt_num, v) relationship holds for given statement number and s is of given statement type.
   * i.e. return the second value of stmt Uses pairs where first value == stmt_num
   *
   * @param stmt_num Statement type of s
   * @return a set of variable names
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStmtUses(std::string stmt_num);

  /**
   * Returns all s where Uses(s, var_name) relationship holds for given variable name and s is of given statement type.
   *
   * @param statement_type Statement type of s
   * @param var_name Name of a variable
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStmtUsing(StatementType statement_type, std::string var_name);

  /**
   * Check if Uses(stmt_num, v) holds for given stmt_num and any variable v.
   * i.e. stmt_num appears as the first value of a stmt Uses relationship pair
   *
   * @param stmt_num Statement num of a statement
   * @return True if condition holds
   */
  virtual bool HasStmtUses(std::string stmt_num);


  /**
   * Check if Uses(stmt_num, var_name) holds for the given stmt_num and var_name.
   *
   * @param stmt_num Statement num of a statement
   * @param var_name Name of a variable
   * @return True if condition holds
   */
  virtual bool IsStmtUsing(std::string stmt_num, std::string var_name);

  //! API for Uses - Procedure

  /**
   * Returns all (p, v) pairs where Uses(p, v) relationship holds.
   *
   * @return a set of pairs (procedure name, variable name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetProcUsesPair();

  /**
   * Returns all p where Uses(p, v) relationship holds.
   * i.e. return the first value of proc Uses pairs
   *
   * @return a set of procedure names
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProcUsesFirst();

  /**
   * Returns all v where Uses(proc_name, v) relationship holds for given procedure name.
   * i.e. return the second value of Uses pairs where first value == proc_name
   *
   * @param proc_name Name of a procedure
   * @return a set of variable names
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProcUses(std::string proc_name);

  /**
   * Returns all p where Uses(p, var_name) relationship holds for given variable name.
   *
   * @param var_name Name of a variable
   * @return a set of procedure names
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProcUsing(std::string var_name);

  /**
   * Check if Uses(proc_name, v) holds for given proc_name and any variable v.
   * i.e. proc_name appears as the first value of a proc Uses relationship pair
   *
   * @param proc_name Name of a procedure
   * @return True if condition holds
   */
  virtual bool HasProcUses(std::string proc_name);

  /**
   * Check if Uses(proc_name, var_name) holds for the given proc_name and var_name.
   *
   * @param proc_name Name of a procedure
   * @param var_name Name of a variable
   * @return True if condition holds
   */
  virtual bool IsProcUsing(std::string proc_name, std::string var_name);

  //!API for Follows

  /**
   * Returns (statement number, statement number) pairs that have a Follows Relationship
   * with the 2nd statement number being the follower of the first
   * @param statement_type is the statement type of the statement being followed
   * @param statement_type_follower is the statement type of the follower
   * @return a set of pairs (statement number, statement number)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);

  /**
 * Returns the statement numbers of statements followed by a specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementFollowedBy(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements following a specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementFollowing(std::string statement_num, StatementType statement_type);

  /**
   * Returns all s where Follow(s, _) holds, i.e. s has follower and s is of the specified type.
   *
   * @param statement_type Statement type of s
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are followers
   * These statements must be of the specified type
   *
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);

  /**
   * Returns true if the statement in the second argument follows the statement in the first argument
   *
   * @param statement_num statement num of a statement
   * @param statement_num_follower is the statement that should follow the statement in the first argument
   * @return bool
   */
  virtual bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower);

  /**
 * Returns true if there is a follows relationship stored between any statements
 * @return bool
 */
  virtual bool IsAnyFollowsRelationshipPresent();

  //!API for FollowsStar

  /**
   * Returns all (s1, s2) pairs where Follows*(s1, s2) relationship holds and s1 is of type_1 and s2 is of type_2.
   *
   * @param type_1 Statement type of s1
   * @param type_2 Statement type of s2
   * @return a set of pairs {s1_stmt_num, s2_stmt_num}
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetFollowsStarPairs(StatementType type_1, StatementType type_2);

  /**
   * Returns all s where Follows*(stmt_num, s) holds for the given stmt_num and s is of the given statement type.
   *
   * @param stmt_num Statement number
   * @param stmt_type Statement type of s
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStar(std::string stmt_num, StatementType stmt_type);

  /**
   * Returns all s where Follows*(s, stmt_num) holds for the given stmt_num and s is of the given statement type.
   *
   * @param stmt_num Statement number
   * @param stmt_type Statement type of s
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarBy(std::string stmt_num, StatementType stmt_type);

  /**
   * Return s1 for all Follows* (s1, s2) pairs where s1 of the given statement type.
   * i.e. return the first value of all Follows* relationships in program.
   *
   * @param stmt_type Statement type of s1
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarFirst(StatementType stmt_type);

  /**
   * Return s2 for all Follows* (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Follows* relationships in program.
   *
   * @param stmt_type Statement type of s2
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarSecond(StatementType stmt_type);

  /**
   * Check if there is any Follows* relationship in program.
   *
   * @return True if Follows* relationship exists in program, false otherwise
   */
  virtual bool HasFollowsStarRelationship();

  /**
   * Check if there exists any stmt s, where Follows*(stmt_num, s) holds for the given stmt_num.
   * i.e. stmt_num appears as the first value in a Follows* relationship pair.
   *
   * @param stmt_num Statement number
   * @return True is such s exists
   */
  virtual bool HasFollowsStar(std::string stmt_num);

  /**
   * Check if there exists any stmt s, where Follows*(s, stmt_num) holds for the given stmt_num.
   * i.e. stmt_num appears as the second value in a Follows* relationship pair.
   *
   * @param stmt_num Statement number
   * @return True is such s exists
   */
  virtual bool HasFollowsStarBy(std::string stmt_num);

  /**
   * Check if Follows*(stmt_num_1, string stmt_num_2) holds for the given two stmt_num.
   *
   * @param stmt_num_1 Statement number
   * @param stmt_num_2 Statement number
   * @return True is relationship holds.
   */
  virtual bool IsFollowsStar(std::string stmt_num_1, std::string stmt_num_2);

  //!API for Parent

  /**
   * Returns (statement number, statement number) pairs that have a Parent-Child Relationship
   * with the 2nd statement number being the child of the first
   * @param statement_type is the statement type of the statement that is the parent
   * @param statement_type_child is the statement type of the child
   * @return a set of pairs (statement number, statement number)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child);


  /**
 * Returns the statement numbers of statements that are parent of the specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are child of the specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are parents
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are child of another statements
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type);

  /**
   * Returns true if the statement in the first argument is the parent of the statement in the second argument
   * @param statement_num statement num of a statement
   * @param statement_num_child is the statement that is child of the statement in the first argument
   * @return bool
   */
  virtual bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child);

  /**
 * Returns true if there is a Parent relationship stored between any statements
 * @return bool
 */
  virtual bool IsAnyParentRelationshipPresent();


  //!API for ParentStar

  /**
   * Returns (statement number, statement number) pairs that have a Ancestor-Descendant Relationship
   * with the 2nd statement number being the child of the first
   * @param statement_type is the statement type of the statement that is the parent
   * @param statement_type_descendant is the statement type of the child
   * @return a set of pairs (statement number, statement number)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant);


  /**
 * Returns the statement numbers of statements that are ancestors of the specified statement
 * @param statement_num is a specific statement
 * @param statement_type is the constraint on the statements in the set
 * @return a set of statement numbers
 */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are descendants of the specified statement
   * @param statement_num is a specific statement
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num,
                                                                               StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are ancestors of any other statement type
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type);

  /**
   * Returns the statement numbers of statements that are descendants of another statement (any type)
   * These statements must be of the specified type
   * @param statement_type is the constraint on the statements in the set
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type);

  /**
   * Returns true if the statement in the first argument is the ancestor of the statement in the second argument
   * @param statement_num statement num of a statement
   * @param statement_num_descendant is the statement that should is descendant of the statement in the first argument
   * @return bool
   */
  virtual bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant);

  /**
 * Returns true if there is a Parent relationship stored between any statements
 * @return bool
 */
  virtual bool IsAnyAncestorDescendantRelationshipPresent();

  //!API for Pattern

  /**
   * Returns assign statements which match the given expr exactly.
   *
   * @param expr Expression
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignWithExactExpression(std::string expr);

  /**
   * Returns assign statements which contains the given sub_expr.
   *
   * @param sub_expr Subexpression
   * @return a set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignWithPartialExpression(std::string sub_expr);
};

