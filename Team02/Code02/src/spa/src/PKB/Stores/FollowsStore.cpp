#include "FollowsStore.h"

FollowsStore::FollowsStore() = default;

FollowsStore::~FollowsStore() = default;

void FollowsStore::AddFollowsRelation(const StatementNumber& first_statement,
                                      const StatementNumber& second_statement) {
  this->follows_relation_store_.insert(first_statement, second_statement);
  this->follows_star_relation_store_.insert(first_statement, second_statement);

  StatementNumberSet v;
  v = this->follows_star_relation_store_.retrieveFromValue(first_statement);

  while (!v.empty()) {
    StatementNumberSet updated_v;
    for (const auto& p: v) {
      auto arr = this->follows_star_relation_store_.retrieveFromValue(p);
      updated_v.insert(arr.begin(), arr.end());
      this->follows_star_relation_store_.insert(p, second_statement);
    }
    v = updated_v;
  }
}

FollowsStore::StatementStatementPairSet FollowsStore::GetFollowsPairs() {
  return this->follows_relation_store_.retrieveAll();
}

FollowsStore::StatementStatementPairSet FollowsStore::GetFollowsStarPairs() {
  return this->follows_star_relation_store_.retrieveAll();
}

bool FollowsStore::HasFollowsRelation(const StatementNumber& first_statement,
                                      const StatementNumber& second_statement) {
  return this->follows_relation_store_.contains(first_statement, second_statement);
}

bool FollowsStore::HasFollowsStarRelation(const StatementNumber& first_statement,
                                          const StatementNumber& second_statement) {
  return this->follows_star_relation_store_.contains(first_statement, second_statement);
}

bool FollowsStore::HasFollowsRelation() {
  return this->follows_relation_store_.length() > 0;
}

bool FollowsStore::HasFollowsStarRelation() {
  return this->follows_star_relation_store_.length() > 0;
}

bool FollowsStore::HasFollowsStarRelation(const StatementNumber& statement) {
  return this->follows_star_relation_store_.containsKey(statement);
}

bool FollowsStore::HasFollowsStarRelationBy(const StatementNumber& statement) {
  return this->follows_star_relation_store_.containsValue(statement);
}

