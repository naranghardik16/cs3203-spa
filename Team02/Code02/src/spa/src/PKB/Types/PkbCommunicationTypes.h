#pragma once

#include <string>
#include <unordered_set>
#include "PKB/Util/PairHasherUtil.h"

class PkbCommunicationTypes {
 public:
  /**
   * Wrapper return type used by PkbReadFacade to interact with QPS.
   * This encloses a single constraint.
   */
  typedef std::string SingleConstraint;

  /**
   * Wrapper return type used by PkbReadFacade to interact with QPS.
   * This encloses multiple single constraints as a set.
   */
  typedef std::unordered_set<SingleConstraint> SingleConstraintSet;

  /**
   * Wrapper return type used by PkbReadFacade to interact with QPS.
   * This encloses a paired constraint, composed of two single constraints.
   */
  typedef std::pair<SingleConstraint, SingleConstraint> PairConstraint;

  /**
   * Wrapper return type used by PkbReadFacade to interact with QPS.
   * This encloses multiple paired constraints as a set.
   */
  typedef std::unordered_set<PairConstraint, PairHasherUtil::hash_pair> PairConstraintSet;
};
