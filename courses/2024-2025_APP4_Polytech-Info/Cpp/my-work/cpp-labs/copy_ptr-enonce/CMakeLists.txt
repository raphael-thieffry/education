cmake_minimum_required(VERSION 3.8)
project(copy_ptr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GENERAL

set(CMAKE_CXX_STANDARD 17)

if(NOT MSVC)
  add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion)
endif()

include_directories(include)

# TESTS

add_executable(test_copy_ptr tests/copy_ptr.cpp)
add_custom_target(run_test_copy_ptr ALL test_copy_ptr)

add_executable(test_copy_ptr_poly tests/copy_ptr_poly.cpp)
add_custom_target(run_test_copy_ptr_poly test_copy_ptr_poly)
