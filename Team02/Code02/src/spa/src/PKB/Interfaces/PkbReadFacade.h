#pragma once

#include <unordered_set>

#include "General/StatementTypeEnum.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "core/model/Expression.h"

/**
 * Facade implementation consisting of read-only methods
 * which acts as an interface between QPS and PKB
 */
class PkbReadFacade {
 public:
  /**
   * Constructor for PKB's read facade.
   *
   * @param pkb - Instance of PKB.
   */
  PkbReadFacade(PKB& pkb);

  /**
   * Destructor for PKB's read facade.
   */
  ~PkbReadFacade();

  /**
   * Retrieves variables stored in PKB.
   *
   * @return A set of variables that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariables();

  /**
   * Retrieves constants stored in PKB.
   *
   * @return A set of constants that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetConstants();

  /**
   * Retrieves procedures stored in PKB.
   *
   * @return A set of procedures that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProcedures();

  /**
   * Retrieves statements stored in PKB.
   *
   * @return A set of statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatements();

  /**
   * Retrieves read statements stored in PKB.
   *
   * @return A set of read statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetReadStatements();

  /**
   * Retrieves print statements stored in PKB.
   *
   * @return A set of print statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetPrintStatements();

  /**
   * Retrieves call statements stored in PKB.
   *
   * @return A set of call statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetCallStatements();

  /**
   * Retrieves while statements stored in PKB.
   *
   * @return A set of while statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetWhileStatements();

  /**
   * Retrieves if statements stored in PKB.
   *
   * @return A set of if statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetIfStatements();

  /**
   * Retrieves assign statements stored in PKB.
   *
   * @return A set of assign statements that are present in PKB.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignStatements();

  /**
   * Retrieves variables modified by a specific statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @return A set of variables that are modified by the statement.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);

  /**
   * Retrieves (statement number, variable name) pairs that have a Modifies relationship with the statement numbers
   * being constrained to the statement_type specified.
   *
   * @param statement_type - Type of the statement.
   * @return A set of pairs (statement number, variable name).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);

  /**
   * Retrieves statements that modify a specific variable,
   * with the statements being constrained to a type specification.
   *
   * @param variable - The variable which gets modified.
   * @param statement_type - The type of statements required.
   * @return A set of variable names with the given constraints.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsModifiesVariable(std::string variable,
                                                                                   StatementType statement_type);

  /**
   * Retrieves the statements of a given statement type that have a Modifies relationship.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements with the given constraints.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatModify(StatementType statement_type);

  /**
   * Checks if a specific statement and variable have a Modifies relationship.
   *
   * @param statement_number - The statement number representing the statement.
   * @param variable - The variable to be checked for.
   * @return True if such a relationship exists, false otherwise.
   */
  virtual bool HasModifiesStatementRelationship(std::string statement_number, std::string variable);

  /**
   * Retrieves variables modified by a given procedure.
   *
   * @param procedure - The procedure.
   * @return A set of variable names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure);

  /**
   * Retrieves (procedure, variable) pairs that have a Modifies relationship with the statement numbers.
   *
   * @return A set of pairs (procedure, variable).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetModifiesProcedureVariablePairs();

  /**
   * Retrieves procedures that modify a specific variable.
   *
   * @param variable - The variable to be checked for.
   * @return A set of variable names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresModifiesVariable(std::string variable);

  /**
   * Retrieves the procedures that have a Modifies relationship.
   *
   * @return A set of procedure names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresThatModify();

  /**
   * Checks if a specific procedure and variable have a Modifies relationship.
   *
   * @param procedure - The procedure to be checked.
   * @param variable - The variable to be checked.
   * @return True if the procedure and variable have a Modifies relationship, false otherwise.
   */
  virtual bool HasModifiesProcedureRelationship(std::string procedure, std::string variable);

  /**
   * Retrieves all (s, v) pairs where Uses(s, v) relationship holds and s is of given statement type.
   *
   * @param statement_type - The type of statement s.
   * @return A set of pairs (statement, variable).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetUsesStatementVariablePairs(StatementType statement_type);

  /**
   * Retrieves all s where Uses(s, v) relationship holds and s is of given statement type
   * i.e. return the first value of statement Uses pairs.
   *
   * @param statement_type - The type of statement s.
   * @return A set of statement numbers representing statements.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatUses(StatementType statement_type);

  /**
   * Retrieves all v where Uses(statement_num, v) relationship holds for given statement number
   * and s is of given statement type i.e. return the second value of statement
   * Uses pairs where first value == statement_num.
   *
   * @param statement_number - The statement to be checked for.
   * @return A set of variable names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesUsedByStatement(std::string statement_number);

  /**
   * Retrieves all s where Uses(s, variable) relationship holds for given variable
   * name and s is of given statement type.
   *
   * @param statement_type - The type of statement.
   * @param variable - The variable to be checked for.
   * @return A set of statement numbers representing statements.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsUsesVariable(StatementType statement_type,
                                                                               std::string variable);

  /**
   * Checks if Uses(statement_num, variable) holds for the given statement_num and variable.
   *
   * @param statement_number - The statement number representing the statement.
   * @param variable - The variable to be checked for.
   * @return True if condition holds, false otherwise.
   */
  virtual bool HasUsesStatementRelationship(std::string statement_number, std::string variable);

  /**
   * Retrieves all (p, v) pairs where Uses(p, v) relationship holds.
   *
   * @return a set of pairs (procedure name, variable name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetUsesProcedureVariablePairs();

  /**
   * Retrieves all p where Uses(p, v) relationship holds
   * i.e. return the first value of proc Uses pairs.
   *
   * @return A set of procedures.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresThatUse();

  /**
   * Retrieves all v where Uses(procedure, v) relationship holds for given procedure name
   * i.e. return the second value of Uses pairs where first value == procedure.
   *
   * @param procedure -  The name of a procedure.
   * @return A set of variable names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetVariablesUsedByProcedure(std::string procedure);

  /**
   * Retrieves all p where Uses(p, variable) relationship holds for given variable name.
   *
   * @param variable - The variable.
   * @return A set of procedure names.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetProceduresUsesVariable(std::string variable);

  /**
   * Checks if Uses(procedure, variable) holds for the given procedure and variable.
   *
   * @param procedure - The name of a procedure.
   * @param variable - The name of a variable
   * @return True if condition holds, false otherwise.
   */
  virtual bool HasUsesProcedureRelationship(std::string procedure, std::string variable);

  /**
   * Retrieves (statement number, statement number) pairs that have a Follows Relationship
   * with the 2nd statement number being the follower of the first.
   *
   * @param statement_type - The statement type of the statement being followed.
   * @param statement_type_follower - The statement type of the follower.
   * @return A set of pairs (statement number, statement number).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type,
                                                                  StatementType statement_type_follower);

  /**
   * Retrieves the statement numbers of statements followed by a specified statement. 
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementFollowedBy(std::string statement_number,
                                                                            StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements following a specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementFollowing(std::string statement_number,
                                                                           StatementType statement_type);

  /**
   * Retrieves all s where Follow(s, _) holds, i.e. s has follower and s is of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are followers.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);

  /**
   * Retrieves true if the statement in the second argument follows the statement in the first argument
   *
   * @param statement_number - The statement num of a statement.
   * @param statement_number_follower - The statement that should follow the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasFollowsRelationship(std::string statement_number, std::string statement_number_follower);

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
  virtual PkbCommunicationTypes::PairConstraintSet GetFollowsStarPairs(StatementType type_1, StatementType type_2);

  /**
   * Retrieves all s where Follows*(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStar(std::string statement_number,
                                                                    StatementType statement_type);

  /**
   * Retrieves all s where Follows*(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarBy(std::string statement_number,
                                                                      StatementType statement_type);

  /**
   * Return s1 for all Follows* (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Follows* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarFirst(StatementType statement_type);

  /**
   * Return s2 for all Follows* (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Follows* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetFollowsStarSecond(StatementType statement_type);

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
  virtual bool HasFollowsStar(std::string statement_number);

  /**
   * Checks if there exists any statement s, where Follows*(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Follows* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasFollowsStarBy(std::string statement_number);

  /**
   * Checks if Follows*(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsFollowsStar(std::string statement_num_1, std::string statement_num_2);

  //!API for Parent
  /**
   * Retrieves (statement number, statement number) pairs that have a Parent-Child Relationship
   * with the 2nd statement number being the child of the first.
   *
   * @param statement_type - The statement type of the statement that is the parent.
   * @param statement_type_child - The statement type of the child.
   * @return A set of pairs (statement number, statement number).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type,
                                                                       StatementType statement_type_child);

  /**
   * Retrieves the statement numbers of statements that are parent of the specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_number,
                                                                                StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are child of the specified statement.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_number,
                                                                                    StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are parents.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are child of another statements.
   * These statements must be of the specified type.
   *
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type);

  /**
   * Checks if the statement in the first argument is the parent of the statement in the second argument.
   *
   * @param statement_number - The statement num of a statement.
   * @param statement_number_child - The statement that is child of the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasParentChildRelationship(std::string statement_number, std::string statement_number_child);

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
  virtual PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type,
                                                                              StatementType statement_type_descendant);

  /**
   * Retrieves the statement numbers of statements that are ancestors of the specified statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_number,
                                                                                    StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are descendants of the specified statement.
   *
   * @param statement_number - The statement number representing the statement.
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num,
                                                                                       StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are ancestors of any other statement type.
   * These statements must be of the specified type.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type);

  /**
   * Retrieves the statement numbers of statements that are descendants of another statement (any type).
   * These statements must be of the specified type.
   *
   * @param statement_type - The type of statements required.
   * @return A set of statement numbers representing the statements.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type);

  /**
   * Checks if the statement in the first argument is the ancestor of the statement in the second argument.
   *
   * @param statement_number - The Statement num of a statement.
   * @param statement_number_descendant - The statement that should is descendant of the statement in the first argument.
   * @return True if the condition holds, false otherwise.
   */
  virtual bool HasAncestorDescendantRelationship(std::string statement_number,
                                                 std::string statement_number_descendant);

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
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignWithExactExpression(const std::shared_ptr<Expression> &expression);

  /**
   * Retrieves assign statements which contains the given sub_expression.
   *
   * @param sub_expression - The sub expression.
   * @return A set of statement numbers representing the statements.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignWithPartialExpression(const std::shared_ptr<Expression> &sub_expression);

  /**
   * Retrieves if statements and condition variable pairs (stmt number, variable). Where variables are used in the
   * condition statement.
   *
   * @return A set of pairs.
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetIfConditionVariablePair();

  /**
   * Retrieves if statements that uses the given variable in its conditions.
   *
   * @param var_name Name of the variable.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetIfWithConditionVariable(const std::string &var_name);

  /**
   * Retrieves if statements that uses variables in its conditions. e.g. if(1=1) is not counted.
   *
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetIfThatHasConditionVariable();

  /**
   * Retrieves while statements and condition variable pairs (stmt number, variable). Where variables are used in the
   * condition statement.
   *
   * @return A set of pairs.
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetWhileConditionVariablePair();

  /**
   * Retrieves while statements that uses the given variable in its conditions.
   *
   * @param var_name Name of the variable.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetWhileWithConditionVariable(const std::string &var_name);

  /**
   * Retrieves while statements that uses variables in its conditions. e.g. while(1=1) is not counted.
   *
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetWhileThatHasConditionVariable();

  /**
 * Retrieves all the variables of a particular expression in the expression store.
 *
 * @param expression - The expression to retrieve the variables from.
 * @return A set of variables that belong to the expression.
 */
  virtual PkbCommunicationTypes::SingleConstraintSet RetrieveAllVariablesOfExpression(std::shared_ptr<Expression> expression);


  //!APi for call
  /**
   * Retrieves call statements and the procedure it calls.
   *
   * @return A set of pairs (call stmt#, procedure name)
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetCallProcedurePair();

  /**
   * Retrieves all the calls pairs where the caller procedure matches the specified procedure.
   *
   * @param procedure - The specified caller procedure.
   * @return
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetAllCallsPairsWithSpecifiedCaller(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the calls star pairs where the caller procedure matches the specified procedure.
   *
   * @param procedure - The specified caller procedure.
   * @return
   */
  virtual PkbCommunicationTypes::PairConstraintSet
  GetAllCallsStarPairsWithSpecifiedCaller(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the calls pairs where the callee procedure matches the specified procedure.
   *
   * @param procedure - The specified callee procedure.
   * @return
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetAllCallsPairsWithSpecifiedCallee(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the calls star pairs where the callee procedure matches the specified procedure.
   *
   * @param procedure - The specified callee procedure.
   * @return
   */
  virtual PkbCommunicationTypes::PairConstraintSet
  GetAllCallsStarPairsWithSpecifiedCallee(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the statements that call the specified procedure.
   *
   * @param procedure - The specified procedure.
   * @return A set of statements that call this procedure.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet
  GetAllCallStatementsFromAProcedure(PkbTypes::PROCEDURE procedure);

  //! QPS-PKB Calls API
  /**
 * Retrieves all calls pairs stored in PKB.
 *
 * @return An unordered set of all the calls pairs.
 */
  virtual PkbCommunicationTypes::PairConstraintSet
  GetAllCallsPairs();

  /**
   * Retrieves all the calls star pairs stored in PKB.
   *
   * @return An unordered set of all the calls star pairs.
   */
  virtual PkbCommunicationTypes::PairConstraintSet
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
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresWithSpecifiedCaller(PkbTypes::PROCEDURE procedure);

  /**
  * Retrieves all procedures that call a specified procedure
  *
  * @param procedure - The specified procedure being called
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresWithSpecifiedCallee(PkbTypes::PROCEDURE procedure);


  /**
  * Retrieves all procedures that are callers in a Calls relationship
  *
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresThatAreCallers();

  /**
  * Retrieves all procedures that are callees in a Calls relationship
  *
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresThatAreCallees();

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
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresWithSpecifiedCallerStar(PkbTypes::PROCEDURE procedure);

  /**
  * Retrieves all procedures that directly or indirectly call a specified procedure
  *
  * @param procedure - The specified procedure being called
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresWithSpecifiedCalleeStar(PkbTypes::PROCEDURE procedure);


  /**
  * Retrieves all procedures that are callers in a CallsStar relationship
  *
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresThatAreCallersStar();

  /**
  * Retrieves all procedures that are callees in a CallsStar relationship
  *
  * @return a set of procedure names
  */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllProceduresThatAreCalleesStar();

  /**
   * Checks if there are any CallsStar relatioship present.
   *
   * @return True is there is a CallsStar relationship present
   */
  virtual bool IsThereAnyCallsStarRelationship();


  //! Affects API

  /**
   * Retrieves all pairs of assign statements with an Affects relationship.
   *
   * @return A set of pairs with format of pairs being <assign_that_affects, assign_that_is_affected>
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetAffectsPairs();

  /**
   * Retrieves all assign statements that are affected by the specified statement.
   *
   * @param stmt_num - the statement that is affecting
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignsAffectedBy(std::string stmt_num);

  /**
   * Retrieves all assign statements that are affecting the specified statement.
   *
   * @param stmt_num - the statement that is affected
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignsAffecting(std::string stmt_num);

  /**
   * Retrieves all assigns that are affected by any other assign statement
   *
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllAssignsThatAreAffected();

  /**
   * Retrieves all assigns that affect any another assign
   *
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllAssignsThatAffect();

  /**
   * Checks if two statements have an Affects relationship
   * @param stmt_num - statement that affects
   * @param stmt_num_being_affected - statement that is affected
   * @return True if there is an Affects relationship else False
   */
  virtual bool HasAffectsRelationship(std::string stmt_num, std::string stmt_num_being_affected);

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
  virtual PkbCommunicationTypes::PairConstraintSet GetAffectsStarPairs();

  /**
   * Retrieves all assign statements that are directly or indirectly affected by the specified statement.
   *
   * @param stmt_num - the statement that is affecting indirectly
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignsAffectedStarBy(std::string stmt_num);

  /**
   * Retrieves all assign statements that are indirectly affecting the specified statement.
   *
   * @param stmt_num - the statement that is affected
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAssignsAffectingStar(std::string stmt_num);

  /**
   * Retrieves all assigns that are affected directly or indirectly by any other assign statement
   *
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllAssignsThatAreAffectedStar();

  /**
   * Retrieves all assigns that directly or indirectly affect any another assign
   *
   * @return A set of statement numbers
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetAllAssignsThatAffectStar();

  /**
   * Checks if two statements have an Affects Star relationship
   * @param stmt_num - statement that affects indirectly
   * @param stmt_num_being_affected - statement that is affected
   * @return True if there is an Affects relationship else False
   */
  virtual bool HasAffectsStarRelationship(std::string stmt_num, std::string stmt_num_being_affected);

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
  virtual PkbCommunicationTypes::PairConstraintSet GetNextPairs(StatementType type_1, StatementType type_2);

  /**
   * Retrieves all s where Next(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNext(std::string statement_number,
                                                             StatementType statement_type);
  /**
   * Retrieves all s where Next(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextBy(std::string statement_number,
                                                               StatementType statement_type);
  /**
   * Return s1 for all Next (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Next relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextFirst(StatementType statement_type);

  /**
   * Return s2 for all Next (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Next relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextSecond(StatementType statement_type);

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
  virtual bool HasNext(std::string statement_number);

  /**
   * Checks if there exists any statement s, where Next(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Next relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNextBy(std::string statement_number);

  /**
   * Checks if Next(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsNext(std::string statement_num_1, std::string statement_num_2);

  //!API for NextStar
  /**
   * Retrieves all (s1, s2) pairs where Next*(s1, s2) relationship holds and s1 is of type_1 and s2 is of type_2.
   *
   * @param type_1 - The statement type of s1.
   * @param type_2 - The statement type of s2.
   * @return A set of pairs (s1_statement_num, s2_statement_num).
   */
  virtual PkbCommunicationTypes::PairConstraintSet GetNextStarPairs(StatementType type_1, StatementType type_2);

  /**
   * Retrieves all s where Next*(statement_num, s) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextStar(std::string statement_number,
                                                                    StatementType statement_type);
  /**
   * Retrieves all s where Next*(s, statement_num) holds for the given statement_num and
   * s is of the given statement type.
   *
   * @param statement_number - The specific statement.
   * @param statement_type - The constraint on the statements in the set.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextStarBy(std::string statement_number,
                                                                      StatementType statement_type);
  /**
   * Return s1 for all Next* (s1, s2) pairs where s1 of the given statement type
   * i.e. return the first value of all Next* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s1.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextStarFirst(StatementType statement_type);

  /**
   * Return s2 for all Next* (s1, s2) pairs where s2 of the given statement type.
   * i.e. return the second value of all Next* relationships in program.
   *
   * @param statement_type - The constraint on the statements in the set ie on s2.
   * @return A set of statement numbers.
   */
  virtual PkbCommunicationTypes::SingleConstraintSet GetNextStarSecond(StatementType statement_type);

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
  virtual bool HasNextStar(std::string statement_number);

  /**
   * Checks if there exists any statement s, where Next*(s, statement_num) holds for the given statement_num.
   * i.e. statement_number appears as the second value in a Next* relationship pair.
   *
   * @param statement_number - The statement number representing the statement.
   * @return True is such s exists, false otherwise.
   */
  virtual bool HasNextStarBy(std::string statement_number);

  /**
   * Checks if Next*(statement_num_1, string statement_num_2) holds for the given two statement_num.
   *
   * @param statement_num_1 - The statement number 1.
   * @param statement_num_2 - The statement number 2.
   * @return True is relationship holds, false otherwise.
   */
  virtual bool IsNextStar(std::string statement_num_1, std::string statement_num_2);

 private:
  PKB& pkb;
};

