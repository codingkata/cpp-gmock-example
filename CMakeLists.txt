# minimum version of cmake utility - usually the one in which this file was created
cmake_minimum_required(VERSION 3.24)

# set the project name
set (PROJECT_NAME "QL-CPP-Tutorial")

# set the PROJECT_ID which will be the target name by changing every
# non-alphanumeric character in PROJECT_NAME to an underscore
string (MAKE_C_IDENTIFIER "${PROJECT_NAME}" PROJECT_ID)
# i.e. CPP Tutorial -> CPP_Tutorial

# change the PROJECT_ID to lower case
string (TOLOWER ${PROJECT_ID} PROJECT_ID)
# i.e. CPP_Tutorial -> cpp_tutorial

# set the project for CMake
project(${PROJECT_NAME})

# include the CMakeLists.txt in src
# this will run everything in that file
add_subdirectory(src)

SET(CMAKE_VERBOSE_MAKEFILE ON)

# add option for test cases
option(BUILD_TESTS "Build tests also for ${PROJECT_NAME}" OFF)


# if tests should be build
# add the subdirectory(with CMakeLists.txt) for tests
if (BUILD_TESTS)

  set(BUILD_GMOCK ON)
	add_subdirectory(external/googletest)
	add_subdirectory(test)
endif()