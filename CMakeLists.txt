
cmake_minimum_required(VERSION 3.10)
project(MMAndConcurrency)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BINARY_ROOT ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Cody style
include(cmake/ClangTidy.cmake)

# Allcators
include_directories(${PROJECT_ROOT})
add_subdirectory(${PROJECT_ROOT}/allocator)
