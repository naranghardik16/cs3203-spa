#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class FollowsStore {
 public:
  FollowsStore();

  ~FollowsStore();



 private:
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_star_store_;
};

