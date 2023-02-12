file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/AbstractDataModels/*.tpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Types/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Clause/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/PatternClauseEvaluator/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/SuchThatClauseEvaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Util/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.cpp")

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/AbstractDataModels/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Types/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Clause/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/PatternClauseEvaluator/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/SuchThatClauseEvaluator/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.h")

add_library(spa ${srcs} ${headers} src/QPS/Evaluator/SuchThatClauseEvaluator/ModifiesPClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/ModifiesPClauseEvaluator.h)
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

