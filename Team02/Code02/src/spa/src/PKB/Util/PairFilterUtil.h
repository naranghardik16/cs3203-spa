#include "PKB/Types/PkbCommunicationTypes.h"

class PairFilterUtil {
 public:
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef PkbCommunicationTypes::PairConstraint Pair;
  typedef std::string SimpleEntity;
  typedef std::function<bool(Pair)> Predicate;

  static PairSet Filter(Predicate f, PairSet ps) {
    PairSet result;
    for (const auto &p : ps) {
      if (f(p)) result.insert(p);
    }

    return result;
  }

  static SingleSet Choose(PairSet ps, bool is_first) {
    SingleSet result;
    for (const auto &p : ps) {
      if (is_first) {
        result.insert(p.first);
      } else {
        result.insert(p.second);
      }
    }

    return result;
  }
};

