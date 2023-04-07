#pragma once

#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/Types/PkbTypes.h"

class TransitiveRelationUtil {
 public:
  typedef PkbCommunicationTypes::PairConstraintSet PairSet;
  typedef PkbCommunicationTypes::SingleConstraintSet SingleSet;
  typedef std::string SimpleEntity;
  typedef std::stack<SimpleEntity> SimpleEntityStack;
  typedef std::unordered_set<SimpleEntity> SimpleEntitySet;
  typedef std::unordered_map<SimpleEntity, SimpleEntitySet> SimpleEntityToMultiSimpleEntityMap;

  static PairSet GetTransitiveRelations(const PairSet &standard_relations) {
    SimpleEntityToMultiSimpleEntityMap map;
    SimpleEntitySet keys;
    for (const auto &p : standard_relations) {
      keys.insert(p.first);
      if (map.count(p.first) > 0) {
        map[p.first].insert(p.second);
      } else {
        map[p.first] = {p.second};
      }
    }

    PairSet result;
    for (const auto &k : keys) {
      SimpleEntityStack s;
      PairSet visited;
      s.push(k);

      while (!s.empty()) {
        SimpleEntity current = s.top();
        s.pop();

        for (const auto &c : map[current]) {
          if (!(visited.count(std::make_pair(k, c)) > 0)) {
            result.insert(std::make_pair(k, c));
            s.push(c);
            visited.insert(std::make_pair(k, c));
          }
        }
      }
    }

    return result;
  }
};

