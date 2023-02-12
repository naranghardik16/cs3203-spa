#pragma once

#include <string>

#include "General/StatementTypeEnum.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/Types/PkbTypes.h"

class StatementStore {
 public:
  /**
   * Constructor for Statement store.
   */
  StatementStore();

  /**
   * Destructor for Statement store.
   */
  ~StatementStore();

  /**
   * Adds a statement to field mapping to the store.
   *
   * @param statement_number - Statement number representing statement to be added.
   * @param field - Field to be added.
   */
  void addStatementAndField(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::FIELD field);

  /**
   * Adds a statement of a particular type to the statement store.
   *
   * @param statement_type - Type of the statement being added.
   * @param statement_number - Statement number representing statement to be added.
   */
  void addStatementForAType(StatementType statement_type, PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieve the type of statement given a statement.
   *
   * @param statement_number - Statement number representing statement for which the type needs to be retrieved.
   * @return The type of the statement for the given statement number.
   */
  StatementType getStatementTypeByNumber(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Retrieves all the statements present in the store for a given type.
   *
   * @param statement_type - Statement type for which the statements are to be retrieved.
   * @return A set of statements for the type given.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> getStatementsFromType(StatementType statement_type);

  /**
   * Retrieves all the statement types present in the store.
   *
   * @return A set of statement types present in the store.
   */
  std::unordered_set<StatementType> getAllStatementTypes();

  /**
   * Retrieves all the statements present in the store.
   *
   * @return A set of statements present in the store.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> getAllStatements();

  /**
   * Retrieves all the fields present in a statement.
   *
   * @param statement_number - Statement number representing the statement.
   * @return A set of fields associated with the statement.
   */
  std::unordered_set<PkbTypes::FIELD> getFieldsForStatement(PkbTypes::STATEMENT_NUMBER statement_number);

 protected:
  OneToManyStore<StatementType, PkbTypes::STATEMENT_NUMBER> type_statement_store;
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::FIELD> statement_field_store;
};

