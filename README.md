
## Building the project with CMAKE


### build executable bin

```shell
rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake .. && make
```

### Building and executing test cases in 'cmake_build' directory

```shell
rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON .. && make 

./test/game_unittest
```

### 构建并运行带有覆盖率的测试用例 in 'cmake_build' directory

```shell
// Just use -DBUILD_TESTS=ON option for cmake.

rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON .. && make

// 执行生成的可执行文件

./test/game_unittest

```

### 在目录 `cmake_build` 下，执行 `lcov` 命令，用于解释并生成 `html` 格式的测试覆盖率报告。

```shell
cd cmake_build

lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out
```

## 使用 GN 和 Ninja 构建项目产物

### 构建 game_demo

```shell
rm -rf out/default && gn gen out/default && ninja -C out/default all
```

上面的命令会在目录 `out/default` 下，生成两个可执行文件，分别是 `game_demo` 和 `game_unittest`。
