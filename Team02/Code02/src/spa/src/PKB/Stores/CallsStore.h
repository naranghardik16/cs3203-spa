#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

/**
 * @class CallsStore
 * Class representing the Calls Store in PKB.
 *
 * The CallsStore class is responsible for maintaining information about the
 * Calls and Calls* relations in the PKB.
 *
 * Calls relation follows OneToMany mapping.
 * Calls* relation follows ManyToMany mapping.
 */
class CallsStore {
 public:
  /**
   * Constructor for Calls store.
   */
  CallsStore();

  /**
   * Destructor for Calls store.
   */
  ~CallsStore();

  /**
   * Adds a calls relation between two procedures.
   *
   * @param caller_procedure - Procedure that calls another procedure.
   * @param callee_procedure - Procedure that is called by another procedure.
   */
  void addCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  /**
   * Add calls statement to procedure name mapping to PKB.
   *
   * @param statement_number - The statement number associated with the call statement.
   * @param procedure - The procedure being called as a part of that statement.
   */
  void addCallStatementToProcedureName(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all calls statement to procedure name mappings in the Calls Store.
   *
   * @return An unordered set of all the call statement to procedure pairs.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
  retrieveAllCallStatementToProcedurePairs();

  /**
   * Retrieves all the Calls relation pairs stored in Calls Store.
   *
   * @return An unordered set of all the Calls relation pairs.
   */
  std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
  retrieveAllCallsPairs();

  /**
   * Retrieves all the Calls* relation pairs stored in the Calls Store.
   *
   * @return An unordered set of all the Calls* relation pairs.
   */
  std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
  retrieveAllCallsStarPairs();

  /**
   * Checks if a Calls relationship exists between two procedures.
   *
   * @param caller_procedure - Procedure that calls another procedure.
   * @param callee_procedure - Procedure that is called by another procedure.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  /**
   * Checks if a Calls* relationship exists between two statements.
   *
   * @param caller_procedure - Procedure that calls another procedure.
   * @param callee_procedure - Procedure that is called by another procedure.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasCallsStarRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure);

  /**
   * Checks if the store contains any Calls relationship.
   *
   * @return True if the store contains at least one Calls relationship, false otherwise.
   */
  bool hasAnyCallsRelation();

  /**
   * Checks if the store contains any Calls* relationship.
   *
   * @return True if the store contains at least one Calls* relationship, false otherwise.
   */
  bool hasAnyCallsStarRelation();

  /**
   * Checks if the procedure has any Calls in the store.
   *
   * @param procedure - The procedure.
   * @return True if the procedure has at least one Calls* in the store with respect to the procedure, false otherwise.
   */
  bool hasCallsStar(PkbTypes::PROCEDURE procedure);

  /**
   * Checks if the procedure has any caller statements for it in the store.
   *
   * @param procedure - The procedure.
   * @return True if the procedure has at least one Calls* in the store with respect to the procedure, false otherwise.
   */
  bool hasCallsStarBy(PkbTypes::PROCEDURE procedure);

 private:
  // Stores the Calls relation OneToMany mapping between two procedures.
  OneToManyStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE> calls_store_;
  // Stores the Calls* relation ManyToMany mapping between two procedures.
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE> calls_star_store_;
  // Stores the Call statement to procedure name
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE> call_to_procedure_store_;
};

