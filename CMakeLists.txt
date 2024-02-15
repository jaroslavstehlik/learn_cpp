cmake_minimum_required(VERSION 3.27)
project(basics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# basics
add_executable(basics "src/main.cpp" "src/unique_pointer.h" "src/vector.h"
        src/shared_pointer.h
        src/test.h)

target_link_libraries(basics GTest::gtest_main)
include(googletest)
enable_testing()
gtest_discover_tests(basics)