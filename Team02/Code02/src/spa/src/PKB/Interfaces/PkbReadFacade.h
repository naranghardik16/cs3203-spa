#pragma once

#include <memory>
#include <unordered_set>

#include "General/StatementTypeEnum.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Pkb.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "core/model/Expression.h"

/**
 * Facade implementation consisting of read-only methods
 * which acts as an interface between QPS and Pkb
 */
class PkbReadFacade {
 public:
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
<<<<<<< HEAD
  typedef PkbCommunicationTypes::PairConstraint Pair;
=======
  typedef std::shared_ptr<CfgNode> CfgNodePtr;
>>>>>>> milestone3

  /**
   * Constructor for Pkb's read facade.
   *
   * @param pkb - Instance of Pkb.
   */
  PkbReadFacade(Pkb &pkb);

  /**
   * Destructor for Pkb's read facade.
   */
  ~PkbReadFacade();

  /**
   * Retrieves variables stored in Pkb.
   *
   * @return A set of variables that are present in Pkb.
   */
  virtual SingleSet GetVariables();

  /**
   * Retrieves constants stored in Pkb.
   *
   * @return A set of constants that are present in Pkb.
   */
  virtual SingleSet GetConstants();

  /**
   * Retrieves procedures stored in Pkb.
   *
   * @return A set of procedures that are present in Pkb.
   */
  virtual SingleSet GetProcedures();

  /**
   * Retrieves statements stored in Pkb.
   *
   * @return A set of statements that are present in Pkb.
   */
  virtual SingleSet GetStatements();

  /**
   * Retrieves read statements stored in Pkb.
   *
   * @return A set of read statements that are present in Pkb.
   */
  virtual SingleSet GetReadStatements();

  /**
   * Retrieves print statements stored in Pkb.
   *
   * @return A set of print statements that are present in Pkb.
   */
  virtual SingleSet GetPrintStatements();

  /**
   * Retrieves call statements stored in Pkb.
   *
   * @return A set of call statements that are present in Pkb.
   */
  virtual SingleSet GetCallStatements();

  /**
   * Retrieves while statements stored in Pkb.
   *
   * @return A set of while statements that are present in Pkb.
   */
  virtual SingleSet GetWhileStatements();

  /**
   * Retrieves if statements stored in Pkb.
   *
   * @return A set of if statements that are present in Pkb.
   */
  virtual SingleSet GetIfStatements();

  /**
   * Retrieves assign statements stored in Pkb.
   *
   * @return A set of assign statements that are present in Pkb.
   */
  virtual SingleSet GetAssignStatements();

  /**
   * Retrieves variables modified by a specific statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @return A set of variables that are modified by the statement.
   */
  virtual SingleSet GetVariablesModifiedByStatement(const StatementNumber &statement_number);

  /**
   * Retrieves (statement number, variable name) pairs that have a Modifies relationship with the statement numbers
   * being constrained to the statement_type specified.
   *
   * @param statement_type - Type of the statement.
   * @return A set of pairs (statement number, variable name).
   */
  virtual PairSet GetModifiesStatementVariablePairs(const StatementType &statement_type);

  /**
   * Retrieves statements that modify a specific variable,
   * with the statements being constrained to a type specification.
   *
   * @param variable - The variable which gets modified.
   * @param statement_type - The type of statements required.
   * @return A set of variable names with the given constraints.
   */
  virtual SingleSet GetStatementsModifiesVariable(const Variable &variable, const StatementType &statement_type);

  /**
   * Retrieves the statements of a given statement type that have a Modifies relationship.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements with the given constraints.
   */
  virtual SingleSet GetStatementsThatModify(const StatementType &statement_type);

  /**
   * Checks if a specific statement and variable have a Modifies relationship.
   *
   * @param statement_number - The statement number representing the statement.
   * @param variable - The variable to be checked for.
   * @return True if such a relationship exists, false otherwise.
   */
  virtual bool HasModifiesStatementRelationship(const StatementNumber &statement_number, const Variable &variable);

  /**
   * Retrieves variables modified by a given procedure.
   *
   * @param procedure - The procedure.
   * @return A set of variable names.
   */
  virtual SingleSet GetVariablesModifiedByProcedure(const Procedure &procedure);

  /**
   * Retrieves (procedure, variable) pairs that have a Modifies relationship with the statement numbers.
   *
   * @return A set of pairs (procedure, variable).
   */
  virtual PairSet GetModifiesProcedureVariablePairs();

  /**
   * Retrieves procedures that modify a specific variable.
   *
   * @param variable - The variable to be checked for.
   * @return A set of variable names.
   */
  virtual SingleSet GetProceduresModifiesVariable(const Variable &variable);

  /**
   * Retrieves the procedures that have a Modifies relationship.
   *
   * @return A set of procedure names.
   */
  virtual SingleSet GetProceduresThatModify();

  /**
   * Checks if a specific procedure and variable have a Modifies relationship.
   *
   * @param procedure - The procedure to be checked.
   * @param variable - The variable to be checked.
   * @return True if the procedure and variable have a Modifies relationship, false otherwise.
   */
  virtual bool HasModifiesProcedureRelationship(const Procedure &procedure, const Variable &variable);

  /**
   * Retrieves all (s, v) pairs where Uses(s, v) relationship holds and s is of given statement type.
   *
   * @param statement_type - The type of statement s.
   * @return A set of pairs (statement, variable).
   */
  virtual PairSet GetUsesStatementVariablePairs(const StatementType &statement_type);

  /**
   * Retrieves all s where Uses(s, v) relationship holds and s is of given statement type
   * i.e. return the first value of statement Uses pairs.
   *
   * @param statement_type - The type of statement s.
   * @return A set of statement numbers representing statements.
   */
  virtual SingleSet GetStatementsThatUses(const StatementType &statement_type);

  /**
   * Retrieves all v where Uses(statement_num, v) relationship holds for given statement number
   * and s is of given statement type i.e. return the second value of statement
   * Uses pairs where first value == statement_num.
   *
   * @param statement_number - The statement to be checked for.
   * @return A set of variable names.
   */
  virtual SingleSet GetVariablesUsedByStatement(const StatementNumber &statement_number);

  /**
   * Retrieves all s where Uses(s, variable) relationship holds for given variable
   * name and s is of given statement type.
   *
   * @param statement_type - The type of statement.
   * @param variable - The variable to be checked for.
   * @return A set of statement numbers representing statements.
   */
  virtual SingleSet GetStatementsUsesVariable(const StatementType &statement_type, const Variable &variable);

  /**
   * Checks if Uses(statement_num, variable) holds for the given statement_num and variable.
   *
   * @param statement_number - The statement number representing the statement.
   * @param variable - The variable to be checked for.
   * @return True if condition holds, false otherwise.
   */
  virtual bool HasUsesStatementRelationship(const StatementNumber &statement_number, const Variable &variable);

  /**
   * Retrieves all (p, v) pairs where Uses(p, v) relationship holds.
   *
   * @return a set of pairs (procedure name, variable name)
   */
  virtual PairSet GetUsesProcedureVariablePairs();

  /**
   * Retrieves all p where Uses(p, v) relationship holds
   * i.e. return the first value of proc Uses pairs.
   *
   * @return A set of procedures.
   */
  virtual SingleSet GetProceduresThatUse();

  /**
   * Retrieves all v where Uses(procedure, v) relationship holds for given procedure name
   * i.e. return the second value of Uses pairs where first value == procedure.
   *
   * @param procedure -  The name of a procedure.
   * @return A set of variable names.
   */
  virtual SingleSet GetVariablesUsedByProcedure(const Procedure &procedure);

  /**
   * Retrieves all p where Uses(p, variable) relationship holds for given variable name.
   *
   * @param variable - The variable.
   * @return A set of procedure names.
   */
  virtual SingleSet GetProceduresUsesVariable(const Variable &variable);

  /**
   * Checks if Uses(procedure, variable) holds for the given procedure and variable.
   *
   * @param procedure - The name of a procedure.
   * @param variable - The name of a variable
   * @return True if condition holds, false otherwise.
   */
  virtual bool HasUsesProcedureRelationship(const Procedure &procedure, const Variable &variable);

  /**
   * Retrieves (statement number, statement number) pairs that have a Follows Relationship
   * with the 2nd statement number being the follower of the first.
   *
   * @param statement_type - The statement type of the statement being followed.
   * @param statement_type_follower - The statement type of the follower.
   * @return A set of pairs (statement number, statement number).
   */
  virtual PairSet GetFollowPairs(const StatementType &statement_type, const StatementType &statement_type_follower);

  /**
   * Retrieves the statement numbers of statements followed by a specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementFollowedBy(const StatementNumber &statement_number,
                                           const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements following a specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementFollowing(const StatementNumber &statement_number, const StatementType &statement_type);

  /**
   * Retrieves all s where Follow(s, _) holds, i.e. s has follower and s is of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsWithFollowers(const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are followers.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementThatAreFollowers(const StatementType &statement_type);

  /**
   * Retrieves true if the statement in the second argument follows the statement in the first argument
   *
   * @param statement_number - The statement num of a statement.
   * @param statement_number_follower - The statement that should follow the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasFollowsRelationship(const StatementNumber &statement_number,
                                      const StatementNumber &statement_number_follower);

  /**
   * Retrieves true if there is a follows relationship stored between any statements.
   *
   * @return True if the condition holds, false otherwise.
   */
  virtual bool IsAnyFollowsRelationshipPresent();

  //!API for FollowsStar
  /**
   * Retrieves all (s1, s2) pairs where Follows*(s1, s2) relationship holds and s1 is of type_1 and s2 is of type_2.
   *
   * @param type_1 - The statement type of s1.
   * @param type_2 - The statement type of s2.
   * @return A set of pairs (s1_statement_num, s2_statement_num).
   */
  virtual PairSet GetFollowsStarPairs(const StatementType &type_1, const StatementType &type_2);

  /**
   * Retrieves all s where Follows*(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetFollowsStar(const StatementNumber &statement_number, const StatementType &statement_type);

  /**
   * Retrieves all s where Follows*(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetFollowsStarBy(const StatementNumber &statement_number, const StatementType &statement_type);

  /**
   * Return s1 for all Follows* (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Follows* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetFollowsStarFirst(const StatementType &statement_type);

  /**
   * Return s2 for all Follows* (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Follows* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetFollowsStarSecond(const StatementType &statement_type);

  /**
   * Checks if there is any Follows* relationship in program.
   *
   * @return True if Follows* relationship exists in program, false otherwise.
   */
  virtual bool HasFollowsStarRelationship();

  /**
   * Checks if there exists any statement s, where Follows*(statement_num, s) holds for the given statement_num.
   * i.e. statement_number appears as the first value in a Follows* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasFollowsStar(const StatementNumber &statement_number);

  /**
   * Checks if there exists any statement s, where Follows*(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Follows* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasFollowsStarBy(const StatementNumber &statement_number);

  /**
   * Checks if Follows*(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsFollowsStar(const StatementNumber &statement_num_1, const StatementNumber &statement_num_2);

  //!API for Parent
  /**
   * Retrieves (statement number, statement number) pairs that have a Parent-Child Relationship
   * with the 2nd statement number being the child of the first.
   *
   * @param statement_type - The statement type of the statement that is the parent.
   * @param statement_type_child - The statement type of the child.
   * @return A set of pairs (statement number, statement number).
   */
  virtual PairSet GetParentChildPairs(const StatementType &statement_type, const StatementType &statement_type_child);

  /**
   * Retrieves the statement numbers of statements that are parent of the specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementThatIsParentOf(const StatementNumber &statement_number,
                                               const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are child of the specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsThatAreChildrenOf(const StatementNumber &statement_number,
                                                   const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are parents.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsThatAreParents(const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are child of another statements.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsThatAreChildren(const StatementType &statement_type);

  /**
   * Checks if the statement in the first argument is the parent of the statement in the second argument.
   *
   * @param statement_number - The statement num of a statement.
   * @param statement_number_child - The statement that is child of the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasParentChildRelationship(const StatementNumber &statement_number,
                                          const StatementNumber &statement_number_child);

  /**
   * Retrieves true if there is a Parent relationship stored between any statements.
   *
   * @return True if the condition holds, false otherwise.
   */
  virtual bool IsAnyParentRelationshipPresent();

  //!API for ParentStar
  /**
   * Retrieves (statement number, statement number) pairs that have a Ancestor-Descendant relationship
   * with the 2nd statement number being the child of the first.
   *
   * @param statement_type - The statement type of the statement that is the parent.
   * @param statement_type_descendant - The statement type of the child
   * @return A set of pairs (statement number, statement number).
   */
  virtual PairSet GetAncestorDescendantPairs(const StatementType &statement_type,
                                             const StatementType &statement_type_descendant);

  /**
   * Retrieves the statement numbers of statements that are ancestors of the specified statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsThatAreAncestorOf(const StatementNumber &statement_number,
                                                   const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are descendants of the specified statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetStatementsThatAreDescendantsOf(const StatementNumber &statement_num,
                                                      const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are ancestors of any other statement type.
   * These statements must be of the specified type.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements.
   */
  virtual SingleSet GetStatementsThatAreAncestors(const StatementType &statement_type);

  /**
   * Retrieves the statement numbers of statements that are descendants of another statement (any type).
   * These statements must be of the specified type.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements.
   */
  virtual SingleSet GetStatementsThatAreDescendants(const StatementType &statement_type);

  /**
   * Checks if the statement in the first argument is the ancestor of the statement in the second argument.
   *
   * @param statement_number - The Statement num of a statement.
   * @param statement_number_descendant - The statement that should is descendant of the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasAncestorDescendantRelationship(const StatementNumber &statement_number,
                                                 const StatementNumber &statement_number_descendant);

  /**
   * Retrieves true if there is a Parent relationship stored between any statements.
   *
   * @return True if the condition holds, false otherwise.
   */
  virtual bool IsAnyAncestorDescendantRelationshipPresent();

  //!API for pattern
  /**
   * Retrieves assign statements which match the given expression exactly.
   *
   * @param expression - The expression.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetAssignWithExactExpression(const ExpressionPtr &expression);

  /**
   * Retrieves assign statements which contains the given sub_expression.
   *
   * @param sub_expression - The sub expression.
   * @return A set of statement numbers representing the statements.
   */
  virtual SingleSet GetAssignWithPartialExpression(const ExpressionPtr &sub_expression);

  /**
   * Retrieves if statements and condition variable pairs (statement number, variable). Where variables are used in the
   * condition statement.
   *
   * @return A set of pairs.
   */
  virtual PairSet GetIfConditionVariablePair();

  /**
   * Retrieves if statements that uses the given variable in its conditions.
   *
   * @param var_name Name of the variable.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetIfWithConditionVariable(const Variable &variable);

  /**
   * Retrieves if statements that uses variables in its conditions. e.g. if(1=1) is not counted.
   *
   * @return A set of statement numbers.
   */
  virtual SingleSet GetIfThatHasConditionVariable();

  /**
   * Retrieves while statements and condition variable pairs (statement number, variable). Where variables are used in the
   * condition statement.
   *
   * @return A set of pairs.
   */
  virtual PairSet GetWhileConditionVariablePair();

  /**
   * Retrieves while statements that uses the given variable in its conditions.
   *
   * @param var_name Name of the variable.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetWhileWithConditionVariable(const Variable &variable);

  /**
   * Retrieves while statements that uses variables in its conditions. e.g. while(1=1) is not counted.
   *
   * @return A set of statement numbers.
   */
  virtual SingleSet GetWhileThatHasConditionVariable();

  /**
 * Retrieves all the variables of a particular expression in the expression store.
 *
 * @param expression - The expression to retrieve the variables from.
 * @return A set of variables that belong to the expression.
 */
  virtual SingleSet RetrieveAllVariablesOfExpression(const ExpressionPtr &expression);


  //!APi for call
  /**
   * Retrieves call statements and the procedure it calls.
   *
   * @return A set of pairs (call statement#, procedure name)
   */
  virtual PairSet GetCallProcedurePair();

  /**
   * Retrieves all the calls pairs where the caller procedure matches the specified procedure.
   *
   * @param procedure - The specified caller procedure.
   * @return
   */
  virtual PairSet GetAllCallsPairsWithSpecifiedCaller(const Procedure &procedure);

  /**
   * Retrieves all the calls star pairs where the caller procedure matches the specified procedure.
   *
   * @param procedure - The specified caller procedure.
   * @return
   */
  virtual PairSet
  GetAllCallsStarPairsWithSpecifiedCaller(const Procedure &procedure);

  /**
   * Retrieves all the calls pairs where the callee procedure matches the specified procedure.
   *
   * @param procedure - The specified callee procedure.
   * @return
   */
  virtual PairSet GetAllCallsPairsWithSpecifiedCallee(const Procedure &procedure);

  /**
   * Retrieves all the calls star pairs where the callee procedure matches the specified procedure.
   *
   * @param procedure - The specified callee procedure.
   * @return
   */
  virtual PairSet
  GetAllCallsStarPairsWithSpecifiedCallee(const Procedure &procedure);

  /**
   * Retrieves all the statements that call the specified procedure.
   *
   * @param procedure - The specified procedure.
   * @return A set of statements that call this procedure.
   */
  virtual SingleSet
  GetAllCallStatementsFromAProcedure(const Procedure &procedure);

  //! QPS-Pkb Calls API
  /**
 * Retrieves all calls pairs stored in Pkb.
 *
 * @return An unordered set of all the calls pairs.
 */
  virtual PairSet
  GetAllCallsPairs();

  /**
   * Retrieves all the calls star pairs stored in Pkb.
   *
   * @return An unordered set of all the calls star pairs.
   */
  virtual PairSet
  GetAllCallsStarPairs();

  /**
   * Checks whether there exists a Calls relation between the specified procedures.
   *
   * @param caller_procedure - The specified caller procedure.
   * @param callee_procedure - The specified callee procedure.
   * @return True if such a relation exists, false otherwise.
   */
  virtual bool HasCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  /**
   * Checks whether there exists a Calls Star relation between the specified procedures.
   *
   * @param caller_procedure - The specified caller procedure.
   * @param callee_procedure - The specified callee procedure.
   * @return True if such a relation exists, false otherwise.
   */
  virtual bool HasCallsStarRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  /**
  * Retrieves all procedures that are being called by the specified procedure.
  *
  * @param procedure - The specified caller procedure
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresWithSpecifiedCaller(const Procedure &procedure);

  /**
  * Retrieves all procedures that call a specified procedure
  *
  * @param procedure - The specified procedure being called
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresWithSpecifiedCallee(const Procedure &procedure);

  /**
  * Retrieves all procedures that are callers in a Calls relationship
  *
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresThatAreCallers();

  /**
  * Retrieves all procedures that are callees in a Calls relationship
  *
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresThatAreCallees();

  /**
   * Checks if there are any Calls relatioship present.
   *
   * @return True is there is a Calls relationship present
   */
  virtual bool IsThereAnyCallsRelationship();

  /**
  * Retrieves all procedures that are being called directly or indirectly by the specified procedure.
  *
  * @param procedure - The specified caller procedure that is the caller in a CallsStar relationship
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresWithSpecifiedCallerStar(const Procedure &procedure);

  /**
  * Retrieves all procedures that directly or indirectly call a specified procedure
  *
  * @param procedure - The specified procedure being called
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresWithSpecifiedCalleeStar(const Procedure &procedure);

  /**
  * Retrieves all procedures that are callers in a CallsStar relationship
  *
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresThatAreCallersStar();

  /**
  * Retrieves all procedures that are callees in a CallsStar relationship
  *
  * @return a set of procedure names
  */
  virtual SingleSet GetAllProceduresThatAreCalleesStar();

  /**
   * Checks if there are any CallsStar relatioship present.
   *
   * @return True is there is a CallsStar relationship present
   */
  virtual bool IsThereAnyCallsStarRelationship();

  virtual Procedure GetProcedureFromCallStatement(const StatementNumber &statement_number);

  //! Affects API

  /**
   * Retrieves all pairs of assign statements with an Affects relationship.
   *
   * @return A set of pairs with format of pairs being <assign_that_affects, assign_that_is_affected>
   */
  virtual PairSet GetAffectsPairs();

  /**
   * Retrieves all assign statements that are affected by the specified statement.
   *
   * @param statement_num - the statement that is affecting
   * @return A set of statement numbers
   */
  virtual SingleSet GetAssignsAffectedBy(const StatementNumber &statement_number);

  /**
   * Retrieves all assign statements that are affecting the specified statement.
   *
   * @param statement_num - the statement that is affected
   * @return A set of statement numbers
   */
  virtual SingleSet GetAssignsAffecting(const StatementNumber &statement_number);

  /**
   * Retrieves all assigns that are affected by any other assign statement
   *
   * @return A set of statement numbers
   */
  virtual SingleSet GetAllAssignsThatAreAffected();

  /**
   * Retrieves all assigns that affect any another assign
   *
   * @return A set of statement numbers
   */
  virtual SingleSet GetAllAssignsThatAffect();

  /**
   * Checks if two statements have an Affects relationship
   * @param statement_num - statement that affects
   * @param statement_num_being_affected - statement that is affected
   * @return True if there is an Affects relationship else False
   */
  virtual bool HasAffectsRelationship(const StatementNumber &statement_number,
                                      const StatementNumber &statement_number_being_affected);

  /**
   * Checks if there is any Affects Relationship present between any assign statements.
   * @return True is there is Affects Relationship stored, else False
   */
  virtual bool IsThereAnyAffectsRelationship();

  //! AffectsStar API

  /**
   * Retrieves all pairs of assign statements with an AffectsStar relationship.
   *
   * @return A set of pairs with format of pairs being <assign_that_affects_star, assign_that_is_affected>
   */
  virtual PairSet GetAffectsStarPairs();

  /**
   * Retrieves all assign statements that are directly or indirectly affected by the specified statement.
   *
   * @param statement_num - the statement that is affecting indirectly
   * @return A set of statement numbers
   */
  virtual SingleSet GetAssignsAffectedStarBy(const StatementNumber &statement_number);

  /**
   * Retrieves all assign statements that are indirectly affecting the specified statement.
   *
   * @param statement_num - the statement that is affected
   * @return A set of statement numbers
   */
  virtual SingleSet GetAssignsAffectingStar(const StatementNumber &statement_number);

  /**
   * Retrieves all assigns that are affected directly or indirectly by any other assign statement
   *
   * @return A set of statement numbers
   */
  virtual SingleSet GetAllAssignsThatAreAffectedStar();

  /**
   * Retrieves all assigns that directly or indirectly affect any another assign
   *
   * @return A set of statement numbers
   */
  virtual SingleSet GetAllAssignsThatAffectStar();

  /**
   * Checks if two statements have an Affects Star relationship
   * @param statement_num - statement that affects indirectly
   * @param statement_num_being_affected - statement that is affected
   * @return True if there is an Affects relationship else False
   */
  virtual bool HasAffectsStarRelationship(const StatementNumber &statement_number,
                                          const StatementNumber &statement_number_being_affected);

  /**
   * Checks if there is any AffectsStars Relationship present between any assign statements.
   * @return True is there is AffectsStars Relationship stored, else False
   */
  virtual bool IsThereAnyAffectsStarRelationship();

  //!API for Next
  /**
   * Retrieves all (s1, s2) pairs where Next(s1, s2) relationship holds and s1 is of type_1 and s2 is of type_2.
   *
   * @param type_1 - The statement type of s1.
   * @param type_2 - The statement type of s2.
   * @return A set of pairs (s1_statement_num, s2_statement_num).
   */
  virtual PairSet GetNextPairs(const StatementType &statement_type_1, const StatementType &statement_type_2);

  /**
   * Retrieves all s where Next(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNext(const StatementNumber &statement_number, const StatementType &statement_type);
  /**
   * Retrieves all s where Next(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextBy(const StatementNumber &statement_number, const StatementType &statement_type);
  /**
   * Return s1 for all Next (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Next relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextFirst(const StatementType &statement_type);

  /**
   * Return s2 for all Next (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Next relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextSecond(const StatementType &statement_type);

  /**
   * Checks if there is any Next relationship in program.
   *
   * @return True if Next* relationship exists in program, false otherwise.
   */
  virtual bool HasNextRelationship();

  /**
   * Checks if there exists any statement s, where Next(statement_num, s) holds for the given statement_num.
   * i.e. statement_number appears as the first value in a Next relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNext(const StatementNumber &statement_number);

  /**
   * Checks if there exists any statement s, where Next(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Next relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNextBy(const StatementNumber &statement_number);

  /**
   * Checks if Next(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsNext(const StatementNumber &statement_num_1, const StatementNumber &statement_num_2);

  //!API for NextStar
  /**
   * Retrieves all (s1, s2) pairs where Next*(s1, s2) relationship holds and s1 is of type_1 and s2 is of type_2.
   *
   * @param type_1 - The statement type of s1.
   * @param type_2 - The statement type of s2.
   * @return A set of pairs (s1_statement_num, s2_statement_num).
   */
  virtual PairSet GetNextStarPairs(const StatementType &type_1, const StatementType &type_2);

  /**
   * Retrieves all s where Next*(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextStar(const StatementNumber &statement_number, const StatementType &statement_type);
  /**
   * Retrieves all s where Next*(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextStarBy(const StatementNumber &statement_number, const StatementType &statement_type);
  /**
   * Return s1 for all Next* (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Next* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextStarFirst(const StatementType &statement_type);

  /**
   * Return s2 for all Next* (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Next* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual SingleSet GetNextStarSecond(const StatementType &statement_type);

  /**
   * Checks if there is any Next* relationship in program.
   *
   * @return True if Next* relationship exists in program, false otherwise.
   */
  virtual bool HasNextStarRelationship();

  /**
   * Checks if there exists any statement s, where Next*(statement_num, s) holds for the given statement_num.
   * i.e. statement_number appears as the first value in a Next* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNextStar(const StatementNumber &statement_number);

  /**
   * Checks if there exists any statement s, where Next*(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Next* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNextStarBy(const StatementNumber &statement_number);

  /**
   * Checks if Next*(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsNextStar(const StatementNumber &statement_num_1, const StatementNumber &statement_num_2);

 private:
  Pkb &pkb;
};

