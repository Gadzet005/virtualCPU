cmake_minimum_required(VERSION 3.14)
project(virtualCPU)

add_subdirectory(lib)

# bin
add_executable(Main bin/main.cpp)
target_link_libraries(Main Source)
include_directories(Main PRIVATE lib/include)

# Покрытие тестов
if(ENABLE_COVERAGE)
  find_program(LCOV lcov REQUIRED)
  set(CMAKE_CXX_FLAGS "-O0 -coverage")
  add_custom_target(
    coverage
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
  )
endif()