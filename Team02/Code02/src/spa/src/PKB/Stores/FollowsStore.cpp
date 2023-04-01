#include "FollowsStore.h"

FollowsStore::FollowsStore() = default;

FollowsStore::~FollowsStore() = default;

void FollowsStore::AddFollowsRelation(const StatementNumber &first_statement,
                                      const StatementNumber &second_statement) {
  this->follows_relation_store_.insert(first_statement, second_statement);
}

void FollowsStore::AddFollowsStarRelation() {
  for (const auto &k : this->follows_relation_store_.retrieveAllKeys()) {
    StatementNumberStack s;
    StatementStatementPairSet visited;
    s.push(k);

    while (!s.empty()) {
      StatementNumber current = s.top();
      s.pop();

      auto c = this->follows_relation_store_.retrieveFromKey(current);

      if (k == c || visited.count(std::make_pair(k, c)) > 0) continue;
      this->follows_star_relation_store_.insert(k, c);
      s.push(c);
      visited.insert(std::make_pair(k, c));
    }
  }
}

FollowsStore::StatementStatementPairSet FollowsStore::GetFollowsPairs() {
  return this->follows_relation_store_.retrieveAll();
}

FollowsStore::StatementStatementPairSet FollowsStore::GetFollowsStarPairs() {
  return this->follows_star_relation_store_.retrieveAll();
}

bool FollowsStore::HasFollowsRelation(const StatementNumber &first_statement,
                                      const StatementNumber &second_statement) {
  return this->follows_relation_store_.contains(first_statement, second_statement);
}

bool FollowsStore::HasFollowsStarRelation(const StatementNumber &first_statement,
                                          const StatementNumber &second_statement) {
  return this->follows_star_relation_store_.contains(first_statement, second_statement);
}

bool FollowsStore::HasFollowsRelation() {
  return this->follows_relation_store_.length() > 0;
}

bool FollowsStore::HasFollowsStarRelation() {
  return this->follows_star_relation_store_.length() > 0;
}

bool FollowsStore::HasFollowsStarRelation(const StatementNumber &statement) {
  return this->follows_star_relation_store_.containsKey(statement);
}

bool FollowsStore::HasFollowsStarRelationBy(const StatementNumber &statement) {
  return this->follows_star_relation_store_.containsValue(statement);
}

