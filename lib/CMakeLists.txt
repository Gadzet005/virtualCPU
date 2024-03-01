cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES source/*.cpp)
add_library(Source ${SOURCE_FILES})

include_directories(Source PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB SOURCE_TEST test/*.cpp)
add_executable(Test ${SOURCE_TEST})
target_link_libraries(Test GTest::gtest_main Source)
include(GoogleTest)
gtest_discover_tests(Test)