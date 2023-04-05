#include "Pkb.h"

Pkb::Pkb() {
  entity_store_ = std::make_shared<EntityStore>();
  statement_store_ = std::make_shared<StatementStore>();
  modifies_store_ = std::make_shared<ModifiesStore>();
  follows_store_ = std::make_shared<FollowsStore>();
  uses_store_ = std::make_shared<UsesStore>();
  parent_store_ = std::make_shared<ParentStore>();
  expression_store_ = std::make_shared<ExpressionStore>();
  control_flow_store_ = std::make_shared<ControlFlowStore>();
  assignment_store_ = std::make_shared<AssignmentStore>();
  calls_store_ = std::make_shared<CallsStore>();
  cfg_store_ = std::make_shared<CfgStore>();
  next_store_ = std::make_shared<NextStore>();
}

Pkb::~Pkb() = default;


