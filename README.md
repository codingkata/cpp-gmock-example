## Building the project

rm -rf build && mkdir build && cd build && cmake .. && make

## Building test cases

Just use -DBUILD_TESTS=ON option for cmake.  
rm -rf build && mkdir build && cd build && cmake -DBUILD_TESTS=ON .. && make

## Building test cases with test coverage

Just use -DBUILD_TESTS=ON option for cmake.  
rm -rf build && mkdir build && cd build && cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON .. && make
