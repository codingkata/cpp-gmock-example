# set a variable that contains the list
# of source files to be built for our targets
set(${PROJECT_ID}_TEST_SOURCES
	BoardTest.cpp
	GameTest.cpp
	main.cpp
)

# the ${PROJECT_ID}-test target shall be an executable
add_executable(${PROJECT_ID}_test)

# set the source files to be built into the executable
target_sources(${PROJECT_ID}_test
	PRIVATE
		${${PROJECT_ID}_TEST_SOURCES}
)

# provide private include paths for our executable
target_include_directories(${PROJECT_ID}_test
	PRIVATE
		../include
)

# set the C++ 20 standard
target_compile_features(${PROJECT_ID}_test
	PRIVATE
		cxx_std_20
)

add_test(
	NAME ${PROJECT_ID}-test
	COMMAND ${PROJECT_ID}-test
)

target_link_libraries(${PROJECT_ID}_test
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