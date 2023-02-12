#include "FollowsStore.h"

FollowsStore::FollowsStore() = default;

FollowsStore::~FollowsStore() = default;

void FollowsStore::addFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                      PkbTypes::STATEMENT_NUMBER second_statement) {
  this->follows_store_.insert(first_statement, second_statement);
  this->follows_star_store_.insert(first_statement, second_statement);

  std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> current =
      std::make_pair(first_statement, second_statement);

  PkbTypes::STATEMENT_NUMBER v;

  while (v = this->follows_store_.retrieveFromValue(current.first), !v.empty()) {
    this->follows_star_store_.insert(v, current.second);
    current = std::make_pair(this->follows_store_.retrieveFromValue(current.first), current.first);
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
  return this->follows_store_.length() > 0 || this->follows_star_store_.length() > 0;
}

