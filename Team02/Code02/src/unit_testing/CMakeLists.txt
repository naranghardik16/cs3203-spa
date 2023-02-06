file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QPS/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Interfaces/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/PKB/Stores/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/General/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer/*.cpp")

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(unit_testing ${srcs} ${header} src/QPS/StubPKB/StubPKBReadFacade.cpp src/QPS/StubPKB/StubPKBReadFacade.h)


target_link_libraries(unit_testing spa)
