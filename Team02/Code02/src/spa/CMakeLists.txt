file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/AbstractDataModels/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Types/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Clause/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/*.cpp")

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/General/SpaException/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core/model/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/ValidationHandler/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/AbstractDataModels/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Types/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Clause/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/Evaluator/*.h"

add_library(spa ${srcs} ${headers} src/QPS/Clause/ClauseSyntax.cpp src/QPS/Clause/ClauseSyntax.h src/QPS/Clause/PatternClauseSyntax.cpp src/QPS/Clause/PatternClauseSyntax.h src/QPS/Clause/SuchThatClauseSyntax.cpp src/QPS/Clause/SuchThatClauseSyntax.h src/QPS/Util/QPSTypeDefs.h src/QPS/Util/QueryUtil.cpp src/QPS/Util/QueryUtil.h src/QPS/Evaluator/PqlEvaluator.cpp src/QPS/Evaluator/PqlEvaluator.h src/QPS/Query.cpp src/QPS/Query.h src/QPS/ExpressionParser.cpp src/QPS/ExpressionParser.h src/QPS/Evaluator/PatternClauseEvaluator/AssignPatternClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/UsesClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/UsesClauseEvaluator.h src/QPS/Evaluator/SuchThatClauseEvaluator/ModifiesClauseEvaluator.cpp src/QPS/Evaluator/SuchThatClauseEvaluator/ModifiesClauseEvaluator.h)
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

