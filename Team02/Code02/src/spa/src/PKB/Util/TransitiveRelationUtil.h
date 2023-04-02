#pragma once

#include "PKB/Types/PkbCommunicationTypes.h"

class TransitiveRelationUtil {
 public:
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;

  PairSet GetTransitiveRelations(PairSet standard_relations, SingleSet keys) {
    return {};
  }
};

