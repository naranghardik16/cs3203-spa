#pragma once

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/Types/PkbTypes.h"


/**
 * @class ParentStore
 * Class representing the Parent Store in PKB.
 *
 * The ParentStore class is responsible for maintaining information about the Parent and Parent* relation in the PKB.
 *
 * Parent relation follows OneToMany mapping.
 * Parent* relation follows ManyToMany mapping.
 */
class ParentStore {
 public:
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
  void addParentRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Retrieves all the Parent relation pairs stored in Parent Store.
   *
   * @return An unordered set of all the Parent relation pairs.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllParentPairs();

  /**
   * Retrieves all the Parent* relation pairs stored in the Parent Store.
   *
   * @return An unordered set of all the Parent* relation pairs.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllParentStarPairs();

  /**
   * Checks if a Parent relationship exists between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasParentRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Checks if a Parent* relationship exists between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasParentStarRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Checks if the store contains any Parent relationship.
   *
   * @return True if the store contains at least one Parent relationship, false otherwise.
   */
  bool hasAnyParentRelation();

  /**
   * Checks if the store contains any Parent* relationship.
   *
   * @return True if the store contains at least one Parent* relationship, false otherwise.
   */
  bool hasAnyParentStarRelation();

  /**
   * Checks if any statement has any parents in the store.
   *
   * @param statement - The statement number of the statement.
   * @return True if the statement has at least one parent in the store, false otherwise.
   */
  bool hasParentStar(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Checks if any statement has any children in the store.
   *
   * @param statement - The statement number of the statement.
   * @return True if the statement has at least one child in the store, false otherwise.
   */
  bool hasParentStarBy(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Retrieves all parent statements stored in the store.
   *
   * @return An unordered set of statement numbers representing all the parent statements in the store.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllParents();

  /**
   * Retrieves the parent statement of a given statement stored in the store.
   *
   * @param statement - The statement number of the statement.
   * @return The statement number which is the parent of the given statement.
   */
  PkbTypes::STATEMENT_NUMBER retrieveAllParents(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Retrieves all the statements that are children in the Parent relationship.
   *
   * @return An unordered set of statement numbers representing all the statements that are children.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllChildren();

  /**
   * Retrieves all the statement numbers that are children of the given statement.
   * @param statement - The statement number to retrieve children of.
   * @return - An unordered set of statement numbers representing all children of the given statement.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllChildren(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Retrieve all statements that are parent in the Parent* relationship.
   *
   * @return An unordered set of statement numbers representing all statements that are parent in the Parent* relation.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllAncestors();

  /**
   * Retrieves all statements that are parent of a given statement in the Parent* relationship.
   *
   * @param statement - The statement number to retrieve ancestors of.
   * @return An unordered set of statement numbers representing all statements that are ancestors.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllAncestors(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Retrieves all statement numbers that are children in a Parent* relation (Descendants).
   *
   * @return An unordered set of statement numbers representing all the statements which are descendants.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllDescendants();

  /**
   * Retrieves all statement numbers that are children of a given statement in the Parent* relationship.
   *
   * @param statement - The statement number to retrieve descendants of.
   * @return An unordered set of statement numbers representing all statements that are descendants.
   */
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllDescendants(PkbTypes::STATEMENT_NUMBER statement);

 private:
  // Stores the Parent relation OneToMany mapping between two statements.
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_store_;
  // Stores the Parent* relation ManyToMany mapping between two statements.
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_star_store_;
};
