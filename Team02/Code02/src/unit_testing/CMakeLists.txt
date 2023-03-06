file(GLOB srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/AbstractDataModels/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Util/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/StubPKB/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Cfg/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer/*.cpp")

file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Util/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/StubPKB/*.h")

add_executable(unit_testing ${srcs} ${header})
target_link_libraries(unit_testing spa)

