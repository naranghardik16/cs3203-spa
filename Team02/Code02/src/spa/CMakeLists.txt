file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.h")
add_library(spa ${srcs} ${headers} src/QPS/Clause/ClauseSyntax.cpp src/QPS/Clause/ClauseSyntax.h src/QPS/Clause/PatternClauseSyntax.cpp src/QPS/Clause/PatternClauseSyntax.h src/QPS/Clause/SuchThatClauseSyntax.cpp src/QPS/Clause/SuchThatClauseSyntax.h src/QPS/Util/QPSTypeDefs.h src/QPS/Util/QueryUtil.cpp src/QPS/Util/QueryUtil.h src/QPS/Evaluator/PqlEvaluator.cpp src/QPS/Evaluator/PqlEvaluator.h src/QPS/Query.cpp src/QPS/Query.h src/QPS/ExpressionParser.cpp src/QPS/ExpressionParser.h)
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

