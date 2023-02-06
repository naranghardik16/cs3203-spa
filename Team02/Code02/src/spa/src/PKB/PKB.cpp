#include "PKB.h"

PKB::PKB() {
  entity_store_ = new EntityStore();
  statement_store_ = new StatementStore();
}

PKB::~PKB() = default;


