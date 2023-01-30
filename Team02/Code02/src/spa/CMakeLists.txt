file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/core/model/Program.h src/core/model/Procedure.h src/core/model/Statement.h src/core/model/Expression.h src/core/model/Program.cpp src/core/model/Procedure.cpp src/core/model/Statement.cpp src/core/model/Expression.cpp src/SP/Parser/Parser.cpp src/SP/Parser/Parser.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


