file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QpsPkb/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QpsPkb/ExpressionGeneratorStub/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SpPkb/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/QpsPkb/ExpressionGeneratorStub/*.h")
add_executable(integration_testing ${srcs})


target_link_libraries(integration_testing spa)
