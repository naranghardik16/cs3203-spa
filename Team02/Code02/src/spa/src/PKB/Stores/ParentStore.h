#pragma once

#include <algorithm>
#include <utility>
#include <stack>

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/TransitiveRelationUtil.h"

/**
 * @class ParentStore
 * Class representing the Parent Store in Pkb.
 *
 * The ParentStore class is responsible for maintaining information about the Parent and Parent* relation in the Pkb.
 *
 * Parent relation follows OneToMany mapping.
 * Parent* relation follows ManyToMany mapping.
 */
class ParentStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::pair<StatementNumber, StatementNumber> StatementStatementPair;
  typedef std::unordered_set<StatementStatementPair, PairHasherUtil::hash_pair>
      StatementStatementPairSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef OneToManyStore<StatementNumber, StatementNumber> StatementToMultiStatementStore;
  typedef ManyToManyStore<StatementNumber, StatementNumber> MultiStatementToStatementStore;
  typedef std::stack<StatementNumber> StatementNumberStack;

  /**
   * Constructor for Parent store.
   */
  ParentStore();

  /**
   * Destructor for Parent store.
   */
  ~ParentStore();

  /**
   * Adds a parent relation between two statements.
   *
   * @param first_statement - Statement that comes first, in other words the one that is the parent of the
   * second statement.
   * @param second_statement - Statement that comes second.
   */
  void AddParentRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  void AddParentStarRelation();

  /**
   * Retrieves all the Parent relation pairs stored in Parent Store.
   *
   * @return An unordered set of all the Parent relation pairs.
   */
  StatementStatementPairSet GetParentPairs();

  /**
   * Retrieves all the Parent* relation pairs stored in the Parent Store.
   *
   * @return An unordered set of all the Parent* relation pairs.
   */
  StatementStatementPairSet GetParentStarPairs();

  /**
   * Checks if a Parent relationship exists between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasParentRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  /**
   * Checks if a Parent* relationship exists between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasParentStarRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  /**
   * Checks if the store contains any Parent relationship.
   *
   * @return True if the store contains at least one Parent relationship, false otherwise.
   */
  bool HasParentRelation();

  /**
   * Checks if the store contains any Parent* relationship.
   *
   * @return True if the store contains at least one Parent* relationship, false otherwise.
   */
  bool HasParentStarRelation();

  /**
   * Checks if any statement has any parents in the store.
   *
   * @param statement - The statement number of the statement.
   * @return True if the statement has at least one parent in the store, false otherwise.
   */
  bool HasParentStarRelation(const StatementNumber &statement);

  /**
   * Checks if any statement has any children in the store.
   *
   * @param statement - The statement number of the statement.
   * @return True if the statement has at least one child in the store, false otherwise.
   */
  bool HasParentStarRelationBy(const StatementNumber &statement);

  /**
   * Retrieves all parent statements stored in the store.
   *
   * @return An unordered set of statement numbers representing all the parent statements in the store.
   */
  StatementNumberSet GetParents();

  /**
   * Retrieves the parent statement of a given statement stored in the store.
   *
   * @param statement - The statement number of the statement.
   * @return The statement number which is the parent of the given statement.
   */
  StatementNumber GetParents(const StatementNumber &statement);

  /**
   * Retrieves all the statements that are children in the Parent relationship.
   *
   * @return An unordered set of statement numbers representing all the statements that are children.
   */
  StatementNumberSet GetChildren();

  /**
   * Retrieves all the statement numbers that are children of the given statement.
   * @param statement - The statement number to retrieve children of.
   * @return - An unordered set of statement numbers representing all children of the given statement.
   */
  StatementNumberSet GetChildren(const StatementNumber &statement);

  /**
   * Retrieve all statements that are parent in the Parent* relationship.
   *
   * @return An unordered set of statement numbers representing all statements that are parent in the Parent* relation.
   */
  StatementNumberSet GetAncestors();

  /**
   * Retrieves all statements that are parent of a given statement in the Parent* relationship.
   *
   * @param statement - The statement number to retrieve ancestors of.
   * @return An unordered set of statement numbers representing all statements that are ancestors.
   */
  StatementNumberSet GetAncestors(const StatementNumber &statement);

  /**
   * Retrieves all statement numbers that are children in a Parent* relation (Descendants).
   *
   * @return An unordered set of statement numbers representing all the statements which are descendants.
   */
  StatementNumberSet GetDescendants();

  /**
   * Retrieves all statement numbers that are children of a given statement in the Parent* relationship.
   *
   * @param statement - The statement number to retrieve descendants of.
   * @return An unordered set of statement numbers representing all statements that are descendants.
   */
  StatementNumberSet GetDescendants(const StatementNumber &statement);

 private:
  // Stores the Parent relation OneToMany mapping between two statements.
  StatementToMultiStatementStore parent_relation_store_;

  // Stores the Parent* relation ManyToMany mapping between two statements.
  MultiStatementToStatementStore parent_star_relation_store_;
};
