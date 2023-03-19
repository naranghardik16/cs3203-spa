#include "ParentStore.h"

ParentStore::ParentStore() = default;

ParentStore::~ParentStore() = default;

void ParentStore::AddParentRelation(const StatementNumber& first_statement, const StatementNumber& second_statement) {
  this->parent_relation_store_.insert(first_statement, second_statement);
  this->parent_star_relation_store_.insert(first_statement, second_statement);

  StatementNumberSet parents = this->parent_star_relation_store_.retrieveFromValue(first_statement);

  while (!parents.empty()) {
    StatementNumberSet updated_parents;
    for (const auto& p : parents) {
      StatementNumberSet grand_parents = this->parent_star_relation_store_.retrieveFromValue(p);
      updated_parents.insert(grand_parents.begin(), grand_parents.end());
      this->parent_star_relation_store_.insert(p, second_statement);
    }
    parents = updated_parents;
  }
}

ParentStore::StatementStatementPairSet ParentStore::GetParentPairs() {
  return this->parent_relation_store_.retrieveAll();
}

ParentStore::StatementStatementPairSet ParentStore::GetParentStarPairs() {
  return this->parent_star_relation_store_.retrieveAll();
}

bool ParentStore::HasParentRelation(const StatementNumber& first_statement, const StatementNumber& second_statement) {
  return this->parent_relation_store_.contains(first_statement, second_statement);
}

bool ParentStore::HasParentStarRelation(const StatementNumber& first_statement, const StatementNumber& second_statement) {
  return this->parent_star_relation_store_.contains(first_statement, second_statement);
}

bool ParentStore::HasParentRelation() {
  return this->parent_relation_store_.length() > 0;
}

bool ParentStore::HasParentStarRelation() {
  return this->parent_star_relation_store_.length() > 0;
}

bool ParentStore::HasParentStarRelation(const StatementNumber& statement) {
  return !this->parent_star_relation_store_.retrieveFromValue(statement).empty();
}

bool ParentStore::HasParentStarRelationBy(const StatementNumber& statement) {
  return !this->parent_star_relation_store_.retrieveFromKey(statement).empty();
}

ParentStore::StatementNumberSet ParentStore::GetParents() {
  return this->parent_relation_store_.retrieveAllKeys();
}

ParentStore::StatementNumber ParentStore::GetParents(const StatementNumber& statement) {
  return this->parent_relation_store_.retrieveFromValue(statement);
}

ParentStore::StatementNumberSet ParentStore::GetChildren(const StatementNumber& statement) {
  return this->parent_relation_store_.retrieveFromKey(statement);
}

ParentStore::StatementNumberSet ParentStore::GetChildren() {
  return this->parent_relation_store_.retrieveAllValues();
}

ParentStore::StatementNumberSet ParentStore::GetAncestors() {
  return this->parent_star_relation_store_.retrieveAllKeys();
}

ParentStore::StatementNumberSet ParentStore::GetAncestors(const StatementNumber& statement) {
  return this->parent_star_relation_store_.retrieveFromValue(statement);
}

ParentStore::StatementNumberSet ParentStore::GetDescendants() {
  return this->parent_star_relation_store_.retrieveAllValues();
}

ParentStore::StatementNumberSet ParentStore::GetDescendants(const StatementNumber& statement) {
  return this->parent_star_relation_store_.retrieveFromKey(statement);
}


