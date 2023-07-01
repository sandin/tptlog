cmake_minimum_required(VERSION 3.8)

project(tptlog C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TEST_ENABLED "enable gtest" ON)

add_subdirectory(src)

if(${TEST_ENABLED})
    add_subdirectory(tests)
endif()