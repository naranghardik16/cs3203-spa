#include "FollowsStore.h"

FollowsStore::FollowsStore() {}

FollowsStore::~FollowsStore() {}

void FollowsStore::addFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                                      PkbTypes::STATEMENT_NUMBER statement_number_2) {
  this->follows_store_.insert(statement_number_1, statement_number_2);
  this->follows_star_store_.insert(statement_number_1, statement_number_2);

  std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> current =
      std::make_pair(statement_number_1, statement_number_2);

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

bool FollowsStore::hasFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1_,
                                      PkbTypes::STATEMENT_NUMBER statement_number_2_) {
  return this->follows_store_.contains(statement_number_1_, statement_number_2_);
}

bool FollowsStore::hasAnyFollowsRelation() {
  return this->follows_store_.length() > 0 || this->follows_star_store_.length() > 0;
}

