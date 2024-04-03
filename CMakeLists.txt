cmake_minimum_required(VERSION 3.25)
project(KrystalBall VERSION 0.1
        DESCRIPTION "Simulation Framework"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include some required dependencies
include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        origin/main
#)
#FetchContent_Declare(
#        abseil
#        GIT_REPOSITORY  https://github.com/abseil/abseil-cpp.git
#        GIT_TAG         origin/master
#)
FetchContent_Declare(
        statusmacros
        GIT_REPOSITORY https://github.com/choward1491/status_macros.git
        GIT_TAG        origin/main
)
FetchContent_MakeAvailable(
                            #googletest
                           statusmacros
                           #abseil
                           )

find_package(absl REQUIRED)
find_package(GTest REQUIRED)

# include headers
include_directories(
        src/
        ${absl_INCLUDE_DIRS}
        ${statusmacros_SOURCE_DIR}
        ${googletest_SOURCE_DIR}/googletest/include
        ${googletest_SOURCE_DIR}/googlemock/include
)

# add testing, if possible
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# add the subdirectories with stuff to be built
add_subdirectory(src)