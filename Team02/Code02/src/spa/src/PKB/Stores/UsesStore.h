#pragma once

#include <string>
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Util/PairHasherUtil.h"

/**
 * @class UsesStore
 * Class representing the Uses Store in the PKB.
 *
 * The UsesStore class is responsible for maintaining information about the Uses relation in the PKB.
 * The Uses relation between a statement and a variable is represented as a ManyToMany relationship.
 * The UsesStore class also maintains information about the Uses relation between a procedure and a variable.
 */
class UsesStore {
 public:
  /**
   * Default constructor for UsesStore.
   * Initializes an empty UsesStore object.
   */
  UsesStore();

  /**
   * Default destructor for UsesStore.
   * Responsible for freeing up any memory used by the UsesStore object.
   */
  ~UsesStore();

  /**
   * Add a statement number to variable mapping to the store signifying a uses relationship where the statement
   * uses a given variable.
   *
   * @param statement_number - Statement number representing a statement that uses the variable.
   * @param variable - Variable modified by the statement.
   */
  void addStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);

  /**
   * Add a procedure to variable mapping to the store signifying a uses relationship where the procedure
   * uses a given variable.
   *
   * @param procedure - Procedure that uses the variable.
   * @param variable - Variable modified by the procedure.
   */
  void addProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);

  /**
   * Retrieves all the variables that have a uses relationship with the statement given.
   *
   * @param statement_number - Statement number representing a statement that uses the variable(s).
   * @return A set of variables that have uses relationship with the statement given.
   */
  std::unordered_set<PkbTypes::VARIABLE> retrieveAllVariablesUsedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all the variables that have a uses relationship with the procedure given.
   *
   * @param procedure - Procedure that uses the variable(s)
   * @return A set of variables that have a uses relationship with the procedure given.
   */
  std::unordered_set<PkbTypes::VARIABLE> retrieveAllVariablesUsedByAProcedure(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the statement variable pairs that have a uses relation among themselves.
   *
   * @return A set of pairs of statement number representing statement and variable.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair> retrieveStatementVariablePairs();

  /**
   * Retrieves all the procedure variable pairs that have a uses relationship among themselves.
   *
   * @return A set of pairs of procedure and variable.
   */
  std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair> retrieveProcedureVariablePairs();

  /**
   * Checks if a given statement and variable have a uses relationship between them.
   *
   * @param statement_number - Statement number representing a statement.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasUsesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);

  /**
   * Checks if a given procedure and variable have a uses relationship between them.
   *
   * @param procedure - Procedure to checked for.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasUsesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);

  /**
   * Retrieves all the procedures that have some sort of a uses relationship with some variable.
   *
   * @return A set of procedures satisfying the criteria.
   */
  std::unordered_set<PkbTypes::PROCEDURE> retrieveAllProceduresThatUse();

 protected:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE> uses_statement_variable_;
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE> uses_procedure_variable_;

};