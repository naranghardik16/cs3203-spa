#include <map>
#include <type_traits>

class CachingUtil {
 public:
  template<typename Func, typename ... Param>
  static auto cached(Func func, Param &&... param) {
    using result_type = std::remove_cv_t<std::invoke_result_t<Func, decltype(param)...>>;

    using key_type = std::tuple<Param...>;

    key_type params(param...);

    static std::map<key_type, result_type> cache;

    auto value = cache.find(params);

    if (value != cache.end()) {
      return value->second;
    }

    return cache.insert(std::pair{params, func(std::forward<Param>(param)...)}).first->second;
  }

};
