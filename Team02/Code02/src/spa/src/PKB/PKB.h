#pragma once

#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/FollowsStore.h"
#include "PKB/Stores/ModifiesStore.h"
#include "PKB/Stores/StatementStore.h"

class PKB {
 public:
  /**
   * Entity store that stores primitives of SIMPLE like variables, procedures and constants.
   */
  EntityStore *entity_store_;

  /**
   * Statement store that stores relations concerning statements.
   */
  StatementStore *statement_store_;

  /**
   * Modifies store that stores multi-variate modifies relations among SIMPLE's entities.
   */
  ModifiesStore *modifies_store_;

  /**
   * Follows store that stores multi-variate follows relations among SIMPLE's entities.
   */
  FollowsStore *follows_store_;

  /**
   * Constructor for PKB.
   */
  PKB();

  /**
   * Destructor for PKB.
   */
  ~PKB();

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};

