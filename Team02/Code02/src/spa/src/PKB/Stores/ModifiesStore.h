#pragma once

#include <string>
#include <unordered_set>

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"

class ModifiesStore {
 public:
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
  void addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);

  /**
   * Add a procedure to variable mapping to the store signifying a modifies relationship where the procedure
   * modifies a variable given.
   *
   * @param procedure - Procedure that modifies the variable.
   * @param variable - Variable modified by the procedure.
   */
  void addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);

  /**
   * Retrieves all the variables that have a modifies relationship with the statement given.
   *
   * @param statement_number - Statement number representing a statement that modifies the variable(s).
   * @return A set of variables that have a modifies relationship with the statement given.
   */
  std::unordered_set<PkbTypes::VARIABLE>
  retrieveAllVariablesModifiedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all the variables that have a modifies relationship with the procedure given.
   *
   * @param procedure - Procedure that modifies the variable(s).
   * @return A set of variables that have a modifies relationship with the procedure given.
   */
  std::unordered_set<PkbTypes::VARIABLE>
  retrieveAllVariablesModifiedByAProcedure(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the statement variable pairs that have a modifies relation among themselves.
   *
   * @return A set of pairs of statement number representing statement and variable.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
  retrieveStatementVariablePairs();

  /**
   * Retrieves all the procedure variable pairs that have a modifies relation among themselves.
   *
   * @return A set of pairs of procedure and variable.
   */
  std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
  retrieveProcedureVariablePairs();

  /**
   * Checks if a given statement and variable have a modifies relationship between them.
   *
   * @param statement_number - Statement number representing a statement.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasModifiesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                      PkbTypes::VARIABLE variable);

  /**
   * Checks if a given procedure and variable have a modifies relationship between them.
   *
   * @param procedure - Procedure to be checked for.
   * @param variable - Variable to be checked for.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasModifiesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure,
                                                      PkbTypes::VARIABLE variable);

  /**
   * Retrieves all the procedures that have some sort of a modifies relationship with some variable.
   *
   * @return A set of procedures satisfying the criteria.
   */
  std::unordered_set<PkbTypes::PROCEDURE> retrieveAllProceduresThatModify();

 protected:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE> modifies_statement_variable_;
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE> modifies_procedure_variable_;
};

