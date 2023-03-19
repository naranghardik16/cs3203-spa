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

BENCHMARK(BM_AddingInts)->Arg(21)->Arg(2000)->Arg(20000)->Complexity();
BENCHMARK(BM_AddingLongLongInts)->Arg(21)->Arg(2000)->Arg(20000)->Complexity();

BENCHMARK_MAIN();