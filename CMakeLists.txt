# 指定 cmake 的最小版本
cmake_minimum_required(VERSION 3.24)

# 设置项目名称
set (PROJECT_NAME "game")

# 将项目名称中的空格，变为下划线，例如：CPP Tutorial -> CPP_Tutorial
# 之后，再将其指定为 PROJECT_ID 的值
string (MAKE_C_IDENTIFIER "${PROJECT_NAME}" PROJECT_ID)

# 将 PROJECT_ID 变为小写字母，例如 CPP_Tutorial -> cpp_tutorial
string (TOLOWER ${PROJECT_ID} PROJECT_ID)


# set the project for CMake
project(${PROJECT_NAME})

# 将目录 src 下面的 CMakeLists.txt 包含进来
# 这将运行这个CMake文件的所有内容
add_subdirectory(src)

SET(CMAKE_VERBOSE_MAKEFILE ON)

# 为测试用例添加选项 option
option(BUILD_TESTS "Build tests also for ${PROJECT_NAME}" OFF)


# 如果需要编译测试用例，将子目录 test 和 googletest 下面的 CMakeLists.txt 包含进来，
if (BUILD_TESTS)
  set(BUILD_GMOCK ON)
	add_subdirectory(external/googletest)
	add_subdirectory(test)
endif()

# 添加编译选项，根据 BUILD_COVERAGE 的值来决定是否启用覆盖率
if (BUILD_COVERAGE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0)
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
      add_link_options(--coverage)
    else()
      link_libraries(--coverage)
    endif()
  else()
    message(FATAL_ERROR "Code coverage is only supported for GCC and Clang compilers.")
  endif()
endif()