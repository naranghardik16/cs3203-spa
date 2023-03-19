#pragma once

#include <string>
#include <unordered_set>

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"

/**
 * @class ModifiesStore
 * Class representing the Modifies Store in the Pkb.
 *
 * The ModifiesStore class is responsible for maintaining information about the Modifies relation in the Pkb.
 * The Modifies relation between a statement and a variable is represented as a ManyToMany relationship.
 * The ModifiesStore class also maintains information about the Modifies relation between a procedure and a variable.
 */
class ModifiesStore {
 public:
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Procedure> ProcedureSet;
  typedef std::unordered_set<std::pair<StatementNumber, Variable>, PairHasherUtil::hash_pair> StatementVariablePairSet;
  typedef std::unordered_set<std::pair<Procedure, Variable>, PairHasherUtil::hash_pair> ProcedureVariablePairSet;
  typedef ManyToManyStore<StatementNumber, Variable> MultiStatementVariableStore;
  typedef ManyToManyStore<Procedure, Variable> MultiProcedureVariableSet;

  /**
   * Constructor for Modifies store.
   */
  ModifiesStore();

  /**
   * Destructor for Modifies store.
   */
  ~ModifiesStore();

  /**
   * Add a statement number to variable mapping to the store signifying a modifies relationship where the statement
   * modifies a variable given.
   *
   * @param statement_number - Statement number representing a statement that modifies the variable.
   * @param variable - Variable modified by the statement.
   */
  void AddStatementModifiesVariable(const StatementNumber& statement_number, const Variable& variable);

  /**
   * Add a procedure to variable mapping to the store signifying a modifies relationship where the procedure
   * modifies a variable given.
   *
   * @param procedure - Procedure that modifies the variable.
   * @param variable - Variable modified by the procedure.
   */
  void AddProcedureModifiesVariable(const Procedure& procedure, const Variable& variable);

  /**
   * Retrieves all the variables that have a modifies relationship with the statement given.
   *
   * @param statement_number - Statement number representing a statement that modifies the variable(s).
   * @return A set of variables that have a modifies relationship with the statement given.
   */
  VariableSet GetVariablesModifiedByStatement(const StatementNumber& statement_number);

  /**
   * Retrieves all the variables that have a modifies relationship with the procedure given.
   *
   * @param procedure - Procedure that modifies the variable(s).
   * @return A set of variables that have a modifies relationship with the procedure given.
   */
  VariableSet GetVariablesModifiedByProcedure(const Procedure& procedure);

  /**
   * Retrieves all the statement variable pairs that have a modifies relation among themselves.
   *
   * @return A set of pairs of statement number representing statement and variable.
   */
  StatementVariablePairSet GetStatementVariablePairs();

  /**
   * Retrieves all the procedure variable pairs that have a modifies relation among themselves.
   *
   * @return A set of pairs of procedure and variable.
   */
  ProcedureVariablePairSet GetProcedureVariablePairs();

  /**
   * Checks if a given statement and variable have a modifies relationship between them.
   *
   * @param statement_number - Statement number representing a statement.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasModifiesStatementVariableRelation(const StatementNumber& statement_number, const Variable& variable);

  /**
   * Checks if a given procedure and variable have a modifies relationship between them.
   *
   * @param procedure - Procedure to be checked for.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasModifiesProcedureVariableRelation(const Procedure& procedure, const Variable& variable);

  /**
   * Retrieves all the procedures that have some sort of a modifies relationship with some variable.
   *
   * @return A set of procedures satisfying the criteria.
   */
  ProcedureSet GetProceduresThatModify();

 private:
  MultiStatementVariableStore modifies_statement_variable_store_;
  MultiProcedureVariableSet modifies_procedure_variable_;
};

