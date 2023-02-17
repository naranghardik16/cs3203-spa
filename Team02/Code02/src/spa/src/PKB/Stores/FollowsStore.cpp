#include "FollowsStore.h"
#include <iostream>
#include <algorithm>
#include <iterator>

FollowsStore::FollowsStore() = default;

FollowsStore::~FollowsStore() = default;

void FollowsStore::addFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                      PkbTypes::STATEMENT_NUMBER second_statement) {
  this->follows_store_.insert(first_statement, second_statement);
  this->follows_star_store_.insert(first_statement, second_statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> v;
  v = this->follows_star_store_.retrieveFromValue(first_statement);

  while (!v.empty()) {
    std::unordered_set<PkbTypes::STATEMENT_NUMBER> updated_v;
    for (const auto& p: v) {
      updated_v.insert(this->follows_star_store_.retrieveFromValue(p).begin(),
                       this->follows_star_store_.retrieveFromValue(p).end());
      this->follows_star_store_.insert(p, second_statement);
    }
    v = updated_v;
  }
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                   PairHasherUtil::hash_pair> FollowsStore::retrieveAllFollowsPairs() {
  return this->follows_store_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                   PairHasherUtil::hash_pair> FollowsStore::retrieveAllFollowsStarPairs() {
  return this->follows_star_store_.retrieveAll();
}

bool FollowsStore::hasFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                      PkbTypes::STATEMENT_NUMBER second_statement) {
  return this->follows_store_.contains(std::move(first_statement), std::move(second_statement));
}

bool FollowsStore::hasFollowsStarRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                      PkbTypes::STATEMENT_NUMBER second_statement) {
  return this->follows_star_store_.contains(std::move(first_statement), std::move(second_statement));
}

bool FollowsStore::hasAnyFollowsRelation() {
  return this->follows_store_.length() > 0;
}

bool FollowsStore::hasAnyFollowsStarRelation() {
  return this->follows_star_store_.length() > 0;
}

bool FollowsStore::hasFollowsStar(PkbTypes::STATEMENT_NUMBER statement) {
  return !this->follows_star_store_.retrieveFromValue(statement).empty();
}

bool FollowsStore::hasFollowsStarBy(PkbTypes::STATEMENT_NUMBER statement) {
  return !this->follows_star_store_.retrieveFromKey(statement).empty();
}

