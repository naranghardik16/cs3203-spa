file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/General/LexicalRuleValidator.cpp src/General/LexicalRuleValidator.h src/QPS/Tokenizer.cpp src/QPS/Tokenizer.h src/General/StringUtil.cpp src/General/StringUtil.h src/QPS/QueryParser.cpp src/QPS/QueryParser.h src/General/SpaException/SemanticErrorException.cpp src/General/SpaException/SemanticErrorException.h src/General/SpaException/SyntaxErrorException.cpp src/General/SpaException/SyntaxErrorException.h src/QPS/AbstractSyntaxExtractor.cpp src/QPS/AbstractSyntaxExtractor.h src/General/SpaException/SpaException.cpp src/General/SpaException/SpaException.h
        src/SP/Tokenizer.cpp src/SP/Tokenizer.h src/SP/Token.cpp src/SP/Token.h src/SP/NameToken.cpp src/SP/NameToken.h src/SP/IntegerToken.cpp src/SP/IntegerToken.h src/SP/PunctuationToken.cpp src/SP/PunctuationToken.h src/SP/ArithmeticOperatorToken.cpp src/SP/ArithmeticOperatorToken.h src/SP/RelationalOperatorToken.cpp src/SP/RelationalOperatorToken.h src/SP/ConditionalOperatorToken.cpp src/SP/ConditionalOperatorToken.h
        src/PKB/PKBStores.h src/General/KeyValueStore.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


