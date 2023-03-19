#pragma once

#include <string>

#include "General/StatementTypeEnum.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class StatementStore is a data storage component that maps statements to their types and fields.
 * The class is designed to store statements in a way that makes it easy to retrieve their
 * associated types and fields.
 */
class StatementStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef PkbTypes::FIELD Field;
  typedef std::unordered_set<Field> FieldSet;
  typedef std::unordered_set<StatementType> StatementTypeSet;
  typedef OneToManyStore<StatementType, StatementNumber> TypeToMultiStatementStore;
  typedef OneToManyStore<StatementNumber, Field> StatementToMultiFieldStore;
  
  /**
   * Default constructor for Statement store.
   * Initializes the object of the class.
   */
  StatementStore();

  /**
   * Default destructor for Statement store.
   */
  ~StatementStore();

  /**
   * Adds a statement to field mapping to the store.
   *
   * @param statement_number - Statement number representing statement to be added.
   * @param field - Field to be added.
   */
  void AddStatementAndField(const StatementNumber& statement_number, const Field& field);

  /**
   * Adds a statement of a particular type to the statement store.
   *
   * @param statement_type - Type of the statement being added.
   * @param statement_number - Statement number representing statement to be added.
   */
  void AddStatementAndType(const StatementType& statement_type, const StatementNumber& statement_number);

  /**
   * Retrieve the type of statement given a statement.
   *
   * @param statement_number - Statement number representing statement for which the type needs to be retrieved.
   * @return The type of the statement for the given statement number.
   */
  StatementType GetType(const StatementNumber& statement_number);

  /**
   * Retrieves all the statements present in the store for a given type.
   *
   * @param statement_type - Statement type for which the statements are to be retrieved.
   * @return A set of statements for the type given.
   */
  StatementNumberSet GetStatements(const StatementType& statement_type);

  /**
   * Retrieves all the statement types present in the store.
   *
   * @return A set of statement types present in the store.
   */
  StatementTypeSet GetTypes();

  /**
   * Retrieves all the statements present in the store.
   *
   * @return A set of statements present in the store.
   */
  StatementNumberSet GetStatements();

  /**
   * Retrieves all the fields present in a statement.
   *
   * @param statement_number - Statement number representing the statement.
   * @return A set of fields associated with the statement.
   */
  FieldSet GetFields(const StatementNumber& statement_number);

 private:
  TypeToMultiStatementStore type_statement_store_;
  StatementToMultiFieldStore statement_field_store_;
};

