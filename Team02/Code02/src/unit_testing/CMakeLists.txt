file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(unit_testing ${srcs}
        src/General/TestLexicalRuleValidator.cpp
        src/General/TestStringUtil.cpp
        src/QPS/TestQueryUtil.cpp
        src/QPS/TestTokenizer.cpp
        src/QPS/TestStmtProcToVarHandler.cpp
        src/QPS/TestStmtToStmtHandler.cpp
        src/QPS/TestPatternHandler.cpp
        src/QPS/TestSuchThatBaseHandler.cpp
        src/QPS/TestQpsValidator.cpp
        src/QPS/TestQueryParser.cpp
        src/QPS/Stubs/StubPkb.cpp
        src/QPS/Stubs/StubPkb.h
        src/QPS/TestPqlEvaluator.cpp
        src/SP/Tokenizer/TestTokenizer.cpp
        src/SP/Parser/TestParser.cpp
        src/PKB/TestPKB.cpp src/TestTNode.cpp src/PKB/Interfaces/TestPkbWriteFacade.cpp)

target_link_libraries(unit_testing spa)
