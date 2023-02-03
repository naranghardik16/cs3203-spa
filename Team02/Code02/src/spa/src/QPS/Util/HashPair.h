#pragma once
#include <iostream>
#include <utility>

// A hash function used to hash a pair of any kind
struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2>& p) const
  {
    auto hash_1 = std::hash<T1>{}(p.first);
    auto hash_2 = std::hash<T2>{}(p.second);

    if (hash_1 != hash_2) {
      return hash_1 ^ hash_2;
    }

    // If hash1 == hash2, their XOR is zero.
    return hash_1;
  }
};