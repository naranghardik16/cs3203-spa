file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Stubs/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer/*.cpp")

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Stubs/*.h")

add_executable(unit_testing ${srcs} ${header})


target_link_libraries(unit_testing spa)
