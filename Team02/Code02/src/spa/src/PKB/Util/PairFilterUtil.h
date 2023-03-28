#pragma once

#include <functional>

#include "PKB/Types/PkbCommunicationTypes.h"

class PairFilterUtil {
 public:
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef PkbCommunicationTypes::PairConstraint Pair;
  typedef PkbCommunicationTypes::SingleConstraint Single;
  typedef std::function<bool(Pair)> PairPredicate;
  typedef std::function<bool(Single)> SinglePredicate;
  typedef std::function<Single(Pair)> Function;

  static PairSet Filter(PairPredicate f, PairSet ps) {
    PairSet result;
    for (const auto &p : ps) {
      if (f(p)) result.insert(p);
    }
    return result;
  }

  static SingleSet Filter(SinglePredicate f, SingleSet ss) {
    SingleSet result;
    for (const auto &p : ss) {
      if (f(p)) result.insert(p);
    }
    return result;
  }

  static SingleSet Map(Function f, PairSet ps) {
    SingleSet result;
    for (const auto &p : ps) {
      result.insert(f(p));
    }
    return result;
  }
};

