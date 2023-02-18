#pragma once

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class ControlFlowStore {
 public:



 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, Expression> if_store_;
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, Expression> while_store_;
};
