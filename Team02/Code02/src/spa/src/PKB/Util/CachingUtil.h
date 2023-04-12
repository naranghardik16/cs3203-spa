#pragma once

#include <functional>
#include <map>
#include <type_traits>
#include <vector>

class CachingUtil {
 public:
  template<typename Func>
  static auto Cached(Func func) {
    using result_type = std::remove_cv_t<std::invoke_result_t<Func>>;
    using key_type = std::tuple<Func>;
    key_type function(func);

    static std::map<key_type, result_type> cache;
    memory.push_back([&]() { cache.clear(); });

    auto value = cache.find(function);
    if (value != cache.end()) return value->second;
    return cache.insert(std::pair{function, func()}).first->second;
  }

//  template<typename Func, typename ... Param>
//  static auto Cached(Func func, Param &&... param) {
//    using result_type = std::remove_cv_t<std::invoke_result_t<Func, decltype(param)...>>;
//    using key_type = std::tuple<Func, Param...>;
//
//    key_type t(func, param...);
//
//    static std::map<key_type, result_type> cache;
//    memory.push_back([&]() { cache.clear(); });
//
//    auto value = cache.find(t);
//    if (value != cache.end()) return value->second;
//    return cache.insert(std::pair{t, func(std::forward<Param>(param)...)}).first->second;
//  }
// C5 (Minor) : Commented-out code
// G10 (Minor) : Bad Coding style - implementing functions in header file

  static void ClearCache() {
    for (const auto &p : memory) p();
  }

  static std::vector<std::function<void()>> memory;
};

std::vector<std::function<void()>> CachingUtil::memory = {};
