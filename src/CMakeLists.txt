# set a variable that contains the list
# of source files to be built for our targets
set(${PROJECT_ID}_SOURCES
	Board.cpp
	Game.cpp
	main.cpp
)

# the PROJECT_ID target shall be an executable
add_executable(${PROJECT_ID})

# set the source files to be built into the executable
target_sources(${PROJECT_ID}
	PRIVATE
		${${PROJECT_ID}_SOURCES}
)

# provide private include paths for our executable
target_include_directories(${PROJECT_ID}
	PRIVATE
		../include
)

# set the C++ 20 standard
target_compile_features(${PROJECT_ID}
	PRIVATE
		cxx_std_20
)

add_library(${PROJECT_ID}-static STATIC)

target_sources(${PROJECT_ID}-static
	PRIVATE
		${${PROJECT_ID}_SOURCES}
)

target_include_directories(${PROJECT_ID}-static
	PRIVATE
		../include
)

target_compile_features(${PROJECT_ID}-static
	PRIVATE
		cxx_std_20
)

# clear the ${PROJECT_ID}_SOURCES variable
# so we don't pollute everything
unset (${PROJECT_ID}_SOURCES)