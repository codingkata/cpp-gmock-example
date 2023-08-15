# set a variable that contains the list
# of source files to be built for our targets
set(${PROJECT_ID}_TEST_SOURCES
	BoardTest.cpp
	GameTest.cpp
	main.cpp
)

# the ${PROJECT_ID}-test target shall be an executable
add_executable(${PROJECT_ID}_unittest)

set(UNITTEST  ${PROJECT_ID}_unittest  )
# set the source files to be built into the executable
target_sources(${UNITTEST}
	PRIVATE
		${${PROJECT_ID}_TEST_SOURCES}
)

# provide private include paths for our executable
target_include_directories(${UNITTEST}
	PRIVATE
		../include
)

# set the C++ 20 standard
target_compile_features(${UNITTEST}
	PRIVATE
		cxx_std_20
)

# Set the -O0 flag to disable optimizations during the build of UNITTEST
target_compile_options(${UNITTEST} PRIVATE -O0)

add_test(
	NAME ${UNITTEST}
	COMMAND ${UNITTEST}
)

target_link_libraries(${UNITTEST}
	PUBLIC
		${PROJECT_ID}-static
		gtest
		gmock
)
# coverage option
OPTION (ENABLE_COVERAGE "Use gcov" ON)

MESSAGE(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
IF(ENABLE_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
ENDIF()