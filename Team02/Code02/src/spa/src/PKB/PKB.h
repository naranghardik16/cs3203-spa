#pragma once

#include "PKB/Stores/AssignmentStore.h"
#include "PKB/Stores/CallsStore.h"
#include "PKB/Stores/CFGStore.h"
#include "PKB/Stores/ControlFlowStore.h"
#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/ExpressionStore.h"
#include "PKB/Stores/FollowsStore.h"
#include "PKB/Stores/ModifiesStore.h"
#include "PKB/Stores/NextStore.h"
#include "PKB/Stores/ParentStore.h"
#include "PKB/Stores/StatementStore.h"
#include "PKB/Stores/UsesStore.h"

class PKB {
 public:
  /**
 * Constructor for PKB.
 */
  PKB();

  /**
   * Destructor for PKB.
   */
  ~PKB();

 private:
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
   * Parent store that stores multi-variate parent relation between SIMPLE's entities.
   */
  ParentStore *parent_store_;

  /**
   * Uses store that stores multi-variate uses relation between SIMPLE's entities.
   */
  UsesStore *uses_store_;

  /**
   * Control flow store that stores uni-variate association between if, while statements and their conditions.
   */
  ControlFlowStore *control_flow_store_;

  /**
   * Assignment store that stores uni-variate association between statement and expression.
   */
  AssignmentStore *assignment_store_;

  /**
   * Expression store that contains mappings between expressions and constants, variables it contains.
   */
  ExpressionStore *expression_store_;

  /**
   * Uses store that stores multi-variate calls relation between SIMPLE's entities.
   */
  CallsStore *calls_store_;

  /**
   * CFG Store that stores the control flow graph of the SIMPLE source.
   */
  CFGStore *cfg_store_;

  /**
   * Next Store that stores the next relation between SIMPLE's entities.
   */
  NextStore *next_store_;

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};
