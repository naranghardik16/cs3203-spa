

#include "FollowsStore.h"

FollowsStore::FollowsStore() {}

FollowsStore::~FollowsStore() {}

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
