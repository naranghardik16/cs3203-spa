file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_library(spa ${srcs} ${headers} src/General/LexicalRuleValidator.cpp src/General/LexicalRuleValidator.h src/QPS/Tokenizer.cpp src/QPS/Tokenizer.h src/General/StringUtil.cpp src/General/StringUtil.h src/QPS/QueryParser.cpp src/QPS/QueryParser.h src/General/SpaException/SemanticErrorException.cpp src/General/SpaException/SemanticErrorException.h src/General/SpaException/SyntaxErrorException.cpp src/General/SpaException/SyntaxErrorException.h src/QPS/AbstractSyntaxExtractor.cpp src/QPS/AbstractSyntaxExtractor.h src/General/SpaException/SpaException.cpp src/General/SpaException/SpaException.h
        src/SP/Tokenizer.cpp src/SP/Tokenizer.h src/SP/Token.cpp src/SP/Token.h src/SP/NameToken.cpp src/SP/NameToken.h src/SP/IntegerToken.cpp src/SP/IntegerToken.h src/SP/PunctuationToken.cpp src/SP/PunctuationToken.h src/SP/ArithmeticOperatorToken.cpp src/SP/ArithmeticOperatorToken.h src/SP/RelationalOperatorToken.cpp src/SP/RelationalOperatorToken.h src/SP/ConditionalOperatorToken.cpp src/SP/ConditionalOperatorToken.h
        src/core/model/Program.h src/core/model/Procedure.h src/core/model/Statement.h src/core/model/Expression.h src/core/model/Program.cpp src/core/model/Procedure.cpp src/core/model/Statement.cpp src/core/model/Expression.cpp src/SP/Parser/Parser.cpp src/SP/Parser/Parser.h
        src/SP/Parser/ProcedureParser.cpp src/SP/Parser/ProcedureParser.h src/SP/Parser/EntityParser.cpp src/SP/Parser/EntityParser.h src/SP/Parser/StatementParser.cpp src/SP/Parser/StatementParser.h src/SP/Parser/StatementParserFactory.cpp src/SP/Parser/StatementParserFactory.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


