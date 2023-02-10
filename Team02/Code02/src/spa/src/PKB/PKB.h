#pragma once

#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/StatementStore.h"
#include "PKB/Stores/ModifiesStore.h"
#include "PKB/Stores/FollowsStore.h"

class PKB {
 public:
  PKB();
  ~PKB();

  EntityStore *entity_store_;
  StatementStore *statement_store_;
  ModifiesStore *modifies_store_;
  FollowsStore *follows_store_;

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};

