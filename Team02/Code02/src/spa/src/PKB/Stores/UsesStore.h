#pragma once

#include <string>
#include <unordered_set>

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"

/**
 * @class UsesStore
 * Class representing the Uses Store in the Pkb.
 *
 * The UsesStore class is responsible for maintaining information about the Uses relation in the Pkb.
 * The Uses relation between a statement and a variable is represented as a ManyToMany relationship.
 * The UsesStore class also maintains information about the Uses relation between a procedure and a variable.
 */
class UsesStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Procedure> ProcedureSet;
  typedef std::unordered_set<std::pair<StatementNumber, Variable>, PairHasherUtil::hash_pair>
      StatementVariablePairSet;
  typedef std::unordered_set<std::pair<Procedure, Variable>, PairHasherUtil::hash_pair>
      ProcedureVariablePairSet;
  typedef ManyToManyStore<StatementNumber, Variable> MultiStatementToVariableStore;
  typedef ManyToManyStore<Procedure, Variable> MultiProcedureToVariableStore;

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
  void AddStatementUsesVariable(const StatementNumber &statement_number, const Variable &variable);

  /**
   * Add a procedure to variable mapping to the store signifying a uses relationship where the procedure
   * uses a given variable.
   *
   * @param procedure - Procedure that uses the variable.
   * @param variable - Variable modified by the procedure.
   */
  void AddProcedureUsesVariable(const Procedure &procedure, const Variable &variable);

  /**
   * Retrieves all the variables that have a uses relationship with the statement given.
   *
   * @param statement_number - Statement number representing a statement that uses the variable(s).
   * @return A set of variables that have uses relationship with the statement given.
   */
  VariableSet GetVariablesUsedByStatement(const StatementNumber &statement_number);

  /**
   * Retrieves all the variables that have a uses relationship with the procedure given.
   *
   * @param procedure - Procedure that uses the variable(s)
   * @return A set of variables that have a uses relationship with the procedure given.
   */
  VariableSet GetVariablesUsedByProcedure(const Procedure &procedure);

  /**
   * Retrieves all the statement variable pairs that have a uses relation among themselves.
   *
   * @return A set of pairs of statement number representing statement and variable.
   */
  StatementVariablePairSet GetStatementVariablePairs();

  /**
   * Retrieves all the procedure variable pairs that have a uses relationship among themselves.
   *
   * @return A set of pairs of procedure and variable.
   */
  ProcedureVariablePairSet GetProcedureVariablePairs();

  /**
   * Checks if a given statement and variable have a uses relationship between them.
   *
   * @param statement_number - Statement number representing a statement.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasUsesStatementVariableRelation(const StatementNumber &statement_number, const Variable &variable);

  /**
   * Checks if a given procedure and variable have a uses relationship between them.
   *
   * @param procedure - Procedure to checked for.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasUsesProcedureVariableRelation(const Procedure &procedure, const Variable &variable);

  /**
   * Retrieves all the procedures that have some sort of a uses relationship with some variable.
   *
   * @return A set of procedures satisfying the criteria.
   */
  ProcedureSet retrieveAllProceduresThatUse();

 private:
  MultiStatementToVariableStore uses_statement_variable_store_;
  MultiProcedureToVariableStore uses_procedure_variable_store_;
};