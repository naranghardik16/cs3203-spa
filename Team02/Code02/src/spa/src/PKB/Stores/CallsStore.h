#pragma once

#include <algorithm>

#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/TransitiveRelationUtil.h"

/**
 * @class CallsStore
 * Class representing the Calls Store in Pkb.
 *
 * The CallsStore class is responsible for maintaining information about the
 * Calls and Calls* relations in the Pkb.
 *
 * Calls relation follows OneToMany mapping.
 * Calls* relation follows ManyToMany mapping.
 */
class CallsStore {
 public:
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<std::pair<StatementNumber, Procedure>, PairHasherUtil::hash_pair>
      StatementNumberProcedurePairSet;
  typedef std::unordered_set<std::pair<Procedure, Procedure>, PairHasherUtil::hash_pair>
      ProcedureProcedurePairSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef ManyToManyStore<Procedure, Procedure> MultiProcedureToProcedureStore;
  typedef OneToManyStore<Procedure, StatementNumber> ProcedureToMultiStatementNumberStore;
  typedef std::stack<Procedure> ProcedureStack;

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
  void AddCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure);

  /**
   * Adds all calls star relations, which signify the transitive calls relations.
   */
  void AddCallsStarRelation();

  /**
   * Add calls statement to procedure name mapping to Pkb.
   *
   * @param statement_number - The statement number associated with the call statement.
   * @param procedure - The procedure being called as a part of that statement.
   */
  void AddCallStatementToProcedure(const StatementNumber &statement_number, const Procedure &procedure);

  /**
   * Retrieves all calls statement to procedure name mappings in the Calls Store.
   *
   * @return An unordered set of all the call statement to procedure pairs.
   */
  StatementNumberProcedurePairSet GetCallStatementToProcedurePairs();

  /**
   * Retrieves all the Calls relation pairs stored in Calls Store.
   *
   * @return An unordered set of all the Calls relation pairs.
   */
  ProcedureProcedurePairSet GetCallsPairs();

  /**
   * Retrieves all the Calls* relation pairs stored in the Calls Store.
   *
   * @return An unordered set of all the Calls* relation pairs.
   */
  ProcedureProcedurePairSet GetCallsStarPairs();

  /**
   * Checks if a Calls relationship exists between two procedures.
   *
   * @param caller_procedure - Procedure that calls another procedure.
   * @param callee_procedure - Procedure that is called by another procedure.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure);

  /**
   * Checks if a Calls* relationship exists between two statements.
   *
   * @param caller_procedure - Procedure that calls another procedure.
   * @param callee_procedure - Procedure that is called by another procedure.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasCallsStarRelation(const Procedure &caller_procedure, const Procedure &callee_procedure);

  /**
   * Checks if the store contains any Calls relationship.
   *
   * @return True if the store contains at least one Calls relationship, false otherwise.
   */
  bool HasCallsRelation();

  /**
   * Checks if the store contains any Calls* relationship.
   *
   * @return True if the store contains at least one Calls* relationship, false otherwise.
   */
  bool HasCallsStarRelation();

  /**
   * Checks if the procedure has any calls in the store.
   *
   * @param procedure - The procedure.
   * @return True if the procedure has at least one Calls* in the store with respect to the procedure, false otherwise.
   */
  bool HasCallsStarRelation(const Procedure &procedure);

  /**
   * Checks if the procedure has any caller statements for it in the store.
   *
   * @param procedure - The procedure.
   * @return True if the procedure has at least one Calls* in the store with respect to the procedure, false otherwise.
   */
  bool HasCallsStarRelationBy(const Procedure &procedure);

  /**
   * Retrieves all the statements that call a procedure.
   *
   * @param procedure - The specified procedure.
   * @return A set of statements that call this procedure.
   */
  StatementNumberSet GetCallStatementsFromProcedure(const Procedure &procedure);

  Procedure GetProcedureFromStatement(const StatementNumber &statement_number);

 private:
  // Stores the Calls relation OneToMany mapping between two procedures.
  MultiProcedureToProcedureStore calls_relation_store_;
  // Stores the Calls* relation ManyToMany mapping between two procedures.
  MultiProcedureToProcedureStore calls_star_relation_store_;
  // Stores the procedure name to call statement(s)
  ProcedureToMultiStatementNumberStore procedure_to_call_statement_store_;
};

