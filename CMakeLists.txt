cmake_minimum_required(VERSION 3.8)

project(tptlog C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TEST_ENABLED "enable gtest" ON)

if(UNIX)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(TPT_PLATFORM_LINUX ON)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(TPT_PLATFORM_MAC ON)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(TPT_PLATFORM_IOS ON)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(TPT_PLATFORM_ANDROID ON)
  else()
    set(TPT_PLATFORM_POSIX ON)
  endif()
endif()
if(WIN32)
  set(TPT_PLATFORM_WINDOWS ON)
endif()

add_subdirectory(src)

if(${TEST_ENABLED})
    add_subdirectory(tests)
endif()