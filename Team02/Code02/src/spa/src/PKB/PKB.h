#pragma once

#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/StatementStore.h"
#include "PKB/Stores/ModifiesStore.h"

class PKB {
 public:
  EntityStore *entity_store_;
  StatementStore *statement_store_;
  ModifiesStore *modifies_store_;
  PKB();
  ~PKB();

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};

