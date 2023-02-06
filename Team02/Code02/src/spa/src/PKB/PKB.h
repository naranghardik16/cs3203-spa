#pragma once

#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/StatementStore.h"

class PKB {
 public:
  EntityStore *entity_store_;
  StatementStore *statement_store_;
  PKB();
  ~PKB();

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};

