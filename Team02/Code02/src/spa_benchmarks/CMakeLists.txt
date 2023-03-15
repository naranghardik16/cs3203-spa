project(spa_benchmarks)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
add_subdirectory(lib)

add_executable(spa_benchmarks spa_benchmark.cpp)

target_link_libraries(spa_benchmarks spa)
target_link_libraries(spa_benchmarks benchmark::benchmark)