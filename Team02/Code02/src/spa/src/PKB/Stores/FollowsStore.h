#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

/**
 * @class FollowsStore
 * Class representing the Follows Store in PKB.
 *
 * The FollowsStore class is responsible for maintaining information about the Follows and Follows* relation in the PKB.
 *
 * Follows relation follows OneToOne mapping.
 * Follows* relation follows ManyToMany mapping.
 */
class FollowsStore {
 public:
  /**
   * Constructor for Follows store.
   */
  FollowsStore();

  /**
   * Destructor for Follows store.
   */
  ~FollowsStore();

  /**
   * Adds a follows relationship between two statements into the store.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second, in other words, the one that follows the first statement.
   */
  void addFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Retrieves all the follows relationships present in the store.
   *
   * @return Set of pairs of statements that have a follows relationship. First statement in the pair follows the
   * second statement.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsPairs();

  /**
   * Retrieves all the follows star relationships present in the store.
   *
   * @return Set of pairs of statements that have a follows star relationship.
   * First statement in the pair follows star the second statement.
   */
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsStarPairs();

  /**
   * Checks if there is a follows relationship between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second, in other words, the one that follows the first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Checks if there is a follows star relationship between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second, in other words, the one that follows star the
   * first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool hasFollowsStarRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                              PkbTypes::STATEMENT_NUMBER second_statement);

  /**
   * Checks with the store if there are any follows relationships present in the store.
   *
   * @return True if there are non-zero number of relations in the store, false otherwise.
   */
  bool hasAnyFollowsRelation();

  /**
   * Checks with the store if there are any follows star relationships present in the store.
   *
   * @return True if there are non-zero number of relations in the store, false otherwise.
   */
  bool hasAnyFollowsStarRelation();

  /**
   * Checks if there exists a follows* relationship with a statement as the first statement.
   *
   * @param statement - Statement to check if it has a follows star relationship as first statement.
   * @return True if there is such a relationship, false otherwise.
   */
  bool hasFollowsStar(PkbTypes::STATEMENT_NUMBER statement);

  /**
   * Checks if there exists a follows* relationship with a statement as the second statement.
   *
   * @param statement - Statement to check if it has a follows* relationship as second statement.
   * @return True if there is such a relationship, false otherwise.
   */
  bool hasFollowsStarBy(PkbTypes::STATEMENT_NUMBER statement);

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_star_store_;
};

