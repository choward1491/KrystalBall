cmake_minimum_required(VERSION 3.25)
project(KrystalBall VERSION 0.1
        DESCRIPTION "Simulation Framework"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# define variables to help with finding needed headers
set(ABSEIL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external/abseil-cpp/)
set(GTEST_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googletest/include)
set(GMOCK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googlemock/include)
set(EXTERNAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(PROJ_SRC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# include header
include_directories(external/abseil-cpp/)
include_directories(external)
include_directories(external/googletest/googletest/include)
include_directories(external/googletest/googlemock/include)
include_directories(src/)

# add testing, if possible
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# add the subdirectories with stuff to be built
add_subdirectory(src)
add_subdirectory(external)