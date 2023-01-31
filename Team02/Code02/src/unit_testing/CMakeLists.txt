file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/General/TestLexicalRuleValidator.cpp src/General/TestStringUtil.cpp src/QPS/TestTokenizer.cpp src/QPS/TestAbstractSyntaxExtractor.cpp src/SP/TestTokenizer.cpp src/PKB/TestPkbStores.cpp src/TestTNode.cpp)
target_link_libraries(unit_testing spa)
