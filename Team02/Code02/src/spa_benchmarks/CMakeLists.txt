project(spa_benchmarks)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
include(AddGitSubmodule.cmake)
add_git_submodule(lib)

add_executable(spa_benchmarks spa_benchmark.cpp)

target_link_libraries(spa_benchmarks spa)
target_link_libraries(spa_benchmarks benchmark::benchmark)