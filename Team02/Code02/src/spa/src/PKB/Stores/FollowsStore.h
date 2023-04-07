#pragma once

#include <algorithm>
#include <utility>

#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/TransitiveRelationUtil.h"

/**
 * @class FollowsStore
 * Class representing the Follows Store in Pkb.
 *
 * The FollowsStore class is responsible for maintaining information about the Follows and Follows* relation in the Pkb.
 *
 * Follows relation follows OneToOne mapping.
 * Follows* relation follows ManyToMany mapping.
 */
class FollowsStore {
 public:
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<PkbTypes::STATEMENT_NUMBER> StatementNumberSet;
  typedef std::pair<StatementNumber, StatementNumber> StatementStatementPair;
  typedef std::unordered_set<StatementStatementPair, PairHasherUtil::hash_pair>
      StatementStatementPairSet;
  typedef OneToOneStore<StatementNumber, StatementNumber> StatementToStatementStore;
  typedef ManyToManyStore<StatementNumber, StatementNumber> MultiStatementToStatementStore;
  typedef std::stack<StatementNumber> StatementNumberStack;

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
  void AddFollowsRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  void AddFollowsStarRelation();

  /**
   * Retrieves all the follows relationships present in the store.
   *
   * @return Set of pairs of statements that have a follows relationship. First statement in the pair follows the
   * second statement.
   */
  StatementStatementPairSet GetFollowsPairs();

  /**
   * Retrieves all the follows star relationships present in the store.
   *
   * @return Set of pairs of statements that have a follows star relationship.
   * First statement in the pair follows star the second statement.
   */
  StatementStatementPairSet GetFollowsStarPairs();

  /**
   * Checks if there is a follows relationship between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second, in other words, the one that follows the first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasFollowsRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  /**
   * Checks if there is a follows star relationship between two statements.
   *
   * @param first_statement - Statement that comes first.
   * @param second_statement - Statement that comes second, in other words, the one that follows star the
   * first statement.
   * @return True if such a relation exists, false otherwise.
   */
  bool HasFollowsStarRelation(const StatementNumber &first_statement, const StatementNumber &second_statement);

  /**
   * Checks with the store if there are any follows relationships present in the store.
   *
   * @return True if there are non-zero number of relations in the store, false otherwise.
   */
  bool HasFollowsRelation();

  /**
   * Checks with the store if there are any follows star relationships present in the store.
   *
   * @return True if there are non-zero number of relations in the store, false otherwise.
   */
  bool HasFollowsStarRelation();

  /**
   * Checks if there exists a follows* relationship with a statement as the first statement.
   *
   * @param statement - Statement to check if it has a follows star relationship as first statement.
   * @return True if there is such a relationship, false otherwise.
   */
  bool HasFollowsStarRelation(const StatementNumber &statement);

  /**
   * Checks if there exists a follows* relationship with a statement as the second statement.
   *
   * @param statement - Statement to check if it has a follows* relationship as second statement.
   * @return True if there is such a relationship, false otherwise.
   */
  bool HasFollowsStarRelationBy(const StatementNumber &statement);

 private:
  StatementToStatementStore follows_relation_store_;
  MultiStatementToStatementStore follows_star_relation_store_;
};

