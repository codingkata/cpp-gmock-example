## Building the project

rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake .. && make

## Building and executing test cases in 'cmake_build' directory


rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON .. && make 

./test/game_unittest


## Building test cases with test coverage in 'cmake_build' directory

Just use -DBUILD_TESTS=ON option for cmake.  
rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON .. && make

## generate coverage report by executing following cmd in 'cmake_build' directory.

cd cmake_build
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out
