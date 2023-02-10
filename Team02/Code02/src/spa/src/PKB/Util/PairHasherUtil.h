#pragma once

#include <unordered_set>

class PairHasherUtil {
 public:
  /**
   * Struct which handles hashing pairs, which by default is not possible in C++.
   */
  struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
      auto hash_1 = std::hash<T1>{}(p.first);
      auto hash_2 = std::hash<T2>{}(p.second);

      if (hash_1 != hash_2) {
        return hash_1 ^ hash_2;
      }

      // If hash_1 == hash_2, their XOR is zero.
      return hash_1;
    }
  };
};

