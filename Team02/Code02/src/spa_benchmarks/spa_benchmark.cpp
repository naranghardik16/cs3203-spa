#include <string>
#include "benchmark/benchmark.h"

static void BM_AddingInts(benchmark::State &state) {
  int n = 0;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); i++) {
      n += i;
    }
  }
  state.SetComplexityN(state.range(0));
}

static void BM_AddingLongLongInts(benchmark::State &state) {
  long long int n = 0;
  for (auto _ : state) {
    for (long long int i = 0; i < state.range(0); ++i) {
      n += i;
    }
  }
  state.SetComplexityN(state.range(0));
}

static void runAutotester(std::string source,
                          std::string query,
                          std::string output) {
  const std::string input =
      "../../../cmake-build-debug/src/autotester/autotester " + source + " "
          + query + " " + output;
  std::system(input.c_str());
}

static void BM_RunAutotester(benchmark::State &state) {
  const std::string source =
      "../../../../Tests02/Milestone3/OverkillTests/M3_Optimization_One_source.txt";
  const std::string query =
      "../../../../Tests02/Milestone3/OverkillTests/M3_Optimization_One_queries.txt";
  const std::string
      output = "../../../../Tests02/Result/out.xml > err.txt && rm err.txt";

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      runAutotester(source, query, output);
    }
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_AddingInts)->Arg(21)->Arg(2000)->Arg(20000)->Complexity();
BENCHMARK(BM_AddingLongLongInts)->Arg(21)->Arg(2000)->Arg(20000)->Complexity();
BENCHMARK(BM_RunAutotester)->Arg(1)->Arg(10)->Arg(50)->Complexity();

BENCHMARK_MAIN();