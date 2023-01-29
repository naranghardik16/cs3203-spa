file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/General/LexicalRuleValidator.cpp src/General/LexicalRuleValidator.h src/QPS/Tokenizer.cpp src/QPS/Tokenizer.h src/General/StringUtil.cpp src/General/StringUtil.h src/QPS/QueryParser.cpp src/QPS/QueryParser.h src/QPS/PqlException/SemanticErrorException.cpp src/QPS/PqlException/SemanticErrorException.h src/QPS/PqlException/SyntaxErrorException.cpp src/QPS/PqlException/SyntaxErrorException.h src/QPS/AbstractSyntaxExtractor.cpp src/QPS/AbstractSyntaxExtractor.h src/QPS/PqlException/PqlException.cpp src/QPS/PqlException/PqlException.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


