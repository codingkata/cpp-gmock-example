## Building the project

rm -rf build && mkdir build && cd build && cmake .. && make

## Building and executing test cases in 'build' directory


rm -rf build && mkdir build && cd build && cmake -DBUILD_TESTS=ON .. && make 

./test/game_unittest


## Building test cases with test coverage in 'build' directory

Just use -DBUILD_TESTS=ON option for cmake.  
rm -rf build && mkdir build && cd build && cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON .. && make

## generate coverage report by executing following cmd in 'build' directory.

cd build
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out
