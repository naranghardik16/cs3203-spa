#include "ParentStore.h"

ParentStore::ParentStore() = default;

ParentStore::~ParentStore() = default;

void ParentStore::addParentRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                    PkbTypes::STATEMENT_NUMBER second_statement) {
  this->parent_store_.insert(first_statement, second_statement);
  this->parent_star_store_.insert(first_statement, second_statement);

  std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> current =
      std::make_pair(first_statement, second_statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> children =
      this->parent_store_.retrieveFromKey(current.second);

  while (!children.empty()) {
    std::unordered_set<PkbTypes::STATEMENT_NUMBER> updated_children;

    for (const auto& c : children) {
      this->parent_star_store_.insert(current.first, c);

      std::unordered_set<PkbTypes::STATEMENT_NUMBER> grand_children = this->parent_store_.retrieveFromKey(c);
      if (!grand_children.empty()) {
        updated_children.insert(grand_children.begin(), grand_children.end());
      }
    }
    children = updated_children;
  }
}

//void ParentStore::dfs(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement) {
//  this->parent_star_store_.insert(first_statement, second_statement);
//  std::unordered_set<PkbTypes::STATEMENT_NUMBER> children = this->parent_store_.retrieveFromKey(second_statement);
//  for (const auto& child : children) {
//    this->dfs(first_statement, child);
//  }
//}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
    ParentStore::retrieveAllParentPairs() {
  return this->parent_store_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
    ParentStore::retrieveAllParentStarPairs() {
  return this->parent_star_store_.retrieveAll();
}

bool ParentStore::hasParentRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                    PkbTypes::STATEMENT_NUMBER second_statement) {
  return this->parent_store_.contains(std::move(first_statement), std::move(second_statement));
}

bool ParentStore::hasParentStarRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                        PkbTypes::STATEMENT_NUMBER second_statement) {
  return this->parent_star_store_.contains(std::move(first_statement), std::move(second_statement));
}

bool ParentStore::hasAnyParentRelation() {
  return this->parent_store_.length() > 0;
}

bool ParentStore::hasAnyParentStarRelation() {
  return this->parent_star_store_.length() > 0;
}

bool ParentStore::hasParentStar(PkbTypes::STATEMENT_NUMBER statement) {
  return !this->parent_star_store_.retrieveFromValue(statement).empty();
}

bool ParentStore::hasParentStarBy(PkbTypes::STATEMENT_NUMBER statement) {
  return !this->parent_star_store_.retrieveFromKey(statement).empty();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllParents() {
  return this->parent_store_.retrieveAllKeys();
}

PkbTypes::STATEMENT_NUMBER ParentStore::retrieveAllParents(PkbTypes::STATEMENT_NUMBER statement) {
  return this->parent_store_.retrieveFromValue(statement);
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllChildren(PkbTypes::STATEMENT_NUMBER statement) {
  return this->parent_store_.retrieveFromKey(statement);
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllChildren() {
  return this->parent_store_.retrieveAllValues();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllAncestors() {
  return this->parent_star_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllAncestors(PkbTypes::STATEMENT_NUMBER statement) {
  return this->parent_star_store_.retrieveFromValue(statement);
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllDescendants() {
  return this->parent_star_store_.retrieveAllValues();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER> ParentStore::retrieveAllDescendants(PkbTypes::STATEMENT_NUMBER statement) {
  return this->parent_star_store_.retrieveFromKey(statement);
}


