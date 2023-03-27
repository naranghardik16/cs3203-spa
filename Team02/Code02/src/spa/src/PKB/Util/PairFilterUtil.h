#include "PKB/Types/PkbCommunicationTypes.h"

class PairFilterUtil {
 public:
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef std::string SimpleEntity;
  typedef std::function<bool(SimpleEntity)> Predicate;

  static PairSet Filter(Predicate f, PairSet ps, bool is_first) {
    PairSet result;
    for (const auto &p : ps) {
      if (is_first) {
        if (f(p.first)) result.insert(p);
      } else {
        if (f(p.second)) result.insert(p);
      }
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

