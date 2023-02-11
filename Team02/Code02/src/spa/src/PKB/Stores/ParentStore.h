#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class ParentStore {
 public:
  ParentStore();

  ~ParentStore();


 private:
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_star_store_;
};

