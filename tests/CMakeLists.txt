include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(CMakeSources.txt)

add_executable(TestRunner
    ${TESTS_SOURCES}
    tests_main.cpp
)

target_include_directories(TestRunner PRIVATE
    core
    "${CMAKE_CURRENT_BINARY_DIR}/../_deps/googletest-src/googletest/include" 
)

target_link_libraries(TestRunner PRIVATE
    core
    GTest::GTest
)
