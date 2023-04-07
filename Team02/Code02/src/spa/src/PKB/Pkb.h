#pragma once

#include <memory>

#include "PKB/Stores/AssignmentStore.h"
#include "PKB/Stores/CallsStore.h"
#include "PKB/Stores/CfgStore.h"
#include "PKB/Stores/ControlFlowStore.h"
#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/ExpressionStore.h"
#include "PKB/Stores/FollowsStore.h"
#include "PKB/Stores/ModifiesStore.h"
#include "PKB/Stores/NextStore.h"
#include "PKB/Stores/ParentStore.h"
#include "PKB/Stores/StatementStore.h"
#include "PKB/Stores/UsesStore.h"

class Pkb {
 public:
  /**
   * Constructor for Pkb.
   */
  Pkb();

  /**
   * Destructor for Pkb.
   */
  ~Pkb();

 private:
  /**
   * Entity store that stores primitives of SIMPLE like variables, procedures and constants.
   */
  std::shared_ptr<EntityStore> entity_store_;

  /**
   * Statement store that stores relations concerning statements.
   */
  std::shared_ptr<StatementStore> statement_store_;

  /**
   * Modifies store that stores multi-variate modifies relations among SIMPLE's entities.
   */
  std::shared_ptr<ModifiesStore> modifies_store_;

  /**
   * Follows store that stores multi-variate follows relations among SIMPLE's entities.
   */
  std::shared_ptr<FollowsStore> follows_store_;

  /**
   * Parent store that stores multi-variate parent relation between SIMPLE's entities.
   */
  std::shared_ptr<ParentStore> parent_store_;

  /**
   * Uses store that stores multi-variate uses relation between SIMPLE's entities.
   */
  std::shared_ptr<UsesStore> uses_store_;

  /**
   * Control flow store that stores uni-variate association between if, while statements and their conditions.
   */
  std::shared_ptr<ControlFlowStore> control_flow_store_;

  /**
   * Assignment store that stores uni-variate association between statement and expression.
   */
  std::shared_ptr<AssignmentStore> assignment_store_;

  /**
   * Expression store that contains mappings between expressions and constants, variables it contains.
   */
  std::shared_ptr<ExpressionStore> expression_store_;

  /**
   * Uses store that stores multi-variate calls relation between SIMPLE's entities.
   */
  std::shared_ptr<CallsStore> calls_store_;

  /**
   * CFG Store that stores the control flow graph of the SIMPLE source.
   */
  std::shared_ptr<CfgStore> cfg_store_;

  /**
   * Next Store that stores the next relation between SIMPLE's entities.
   */
  std::shared_ptr<NextStore> next_store_;

  friend class PkbWriteFacade;
  friend class PkbReadFacade;
};
