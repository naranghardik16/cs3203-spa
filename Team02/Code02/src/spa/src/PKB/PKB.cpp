#include "PKB.h"

PKB::PKB() {
  entity_store_ = new EntityStore();
  statement_store_ = new StatementStore();
  modifies_store_ = new ModifiesStore();
  follows_store_ = new FollowsStore();
  uses_store_ = new UsesStore();
  parent_store_ = new ParentStore();
}

PKB::~PKB() = default;


