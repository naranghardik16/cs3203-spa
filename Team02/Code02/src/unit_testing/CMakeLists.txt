file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(unit_testing ${srcs} 
               src/QPS/TestQPSLexicalRuleValidator.cpp src/General/TestStringUtil.cpp src/QPS/TestTokenizer.cpp
               src/QPS/TestAbstractSyntaxExtractor.cpp src/SP/TestTokenizer.cpp src/SP/Parser/TestParser.cpp
               src/General/TestLexicalRuleValidator.cpp src/General/TestStringUtil.cpp
               )

target_link_libraries(unit_testing spa)

