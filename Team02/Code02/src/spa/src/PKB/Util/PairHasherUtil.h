#pragma once

#include <unordered_set>

class PairHasherUtil {
 public:
  template<typename T>
  static void hash_combine(std::size_t &seed, T const &key) {
    std::hash<T> hasher;
    seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  /**
   * Struct which handles hashing pairs, which by default is not possible in C++.
   */
  struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t seed1(0);
        hash_combine(seed1, p.first);
        hash_combine(seed1, p.second);

        std::size_t seed2(0);
        hash_combine(seed2, p.second);
        hash_combine(seed2, p.first);

        return std::min(seed1, seed2);
    }
  };
};

