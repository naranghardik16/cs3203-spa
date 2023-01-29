file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/SP/Tokenizer.cpp src/SP/Tokenizer.h src/SP/Token.cpp src/SP/Token.h src/SP/NameToken.cpp src/SP/NameToken.h src/SP/IntegerToken.cpp src/SP/IntegerToken.h src/SP/PunctuationToken.cpp src/SP/PunctuationToken.h src/SP/ArithmeticOperatorToken.cpp src/SP/ArithmeticOperatorToken.h src/SP/RelationalOperatorToken.cpp src/SP/RelationalOperatorToken.h src/SP/ConditionalOperatorToken.cpp src/SP/ConditionalOperatorToken.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


