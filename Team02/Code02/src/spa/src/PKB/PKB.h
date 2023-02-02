#pragma once

#include "PKB/Stores/EntityStore.h"

class PKB {
 public:
  EntityStore *entity_store_;
  PKB();
  ~PKB();

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};

