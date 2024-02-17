cmake_minimum_required(VERSION 3.14)
project(virtualCPU)

# C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека
file(GLOB SOURCE_FILES lib/source/*.cpp)
add_library(Source ${SOURCE_FILES})

# bin
add_executable(Main bin/main.cpp)
target_link_libraries(Main Source)

include_directories(Source PRIVATE lib/include)

# Покрытие тестов
if(ENABLE_COVERAGE)
  find_program(LCOV lcov REQUIRED)
  set(CMAKE_CXX_FLAGS "-O0 -coverage")
  add_custom_target(
    coverage
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
  )
endif()

# Тесты
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