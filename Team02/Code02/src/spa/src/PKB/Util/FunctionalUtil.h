#pragma once

#include <functional>

#include "PKB/Types/PkbCommunicationTypes.h"

class FunctionalUtil {
 public:
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef PkbCommunicationTypes::PairConstraint Pair;
  typedef PkbCommunicationTypes::SingleConstraint Single;
  typedef std::function<bool(Pair)> PairPredicate;
  typedef std::function<bool(Single)> SinglePredicate;
  typedef std::function<Single(Pair)> PairToSingleFunction;
  typedef std::function<SingleSet(Single)> SingleToSingleSetFunction;

  static PairSet Filter(const PairPredicate &f, const PairSet &ps) {
    PairSet result;
    for (const auto &p : ps) {
      if (f(p)) result.insert(p);
    }
    return result;
  }

  static SingleSet Filter(const SinglePredicate &f, const SingleSet &ss) {
    SingleSet result;
    for (const auto &p : ss) {
      if (f(p)) result.insert(p);
    }
    return result;
  }

  static SingleSet Map(const PairToSingleFunction &f, const PairSet &ps) {
    SingleSet result;
    for (const auto &p : ps) {
      result.insert(f(p));
    }
    return result;
  }

  static PairSet Collect(const SingleToSingleSetFunction &f, const SingleSet &ss) {
    PairSet result;
    for (const auto &s : ss) {
      for (const auto &a : f(s)) result.insert(std::make_pair(s, a));
    }
    return result;
  }
};

