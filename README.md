
## Building the project with CMAKE


### 构建可执行程序 `game`，并保存在 `cmake_build/src` 目录下。

```shell
rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake .. && make
# 执行生成的可执行文件
./src/game
```

### 构建可执行程序 `game_unittest`，并保存在 `cmake_build/src` 目录下。

```shell
rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON .. && make 
# 执行生成的可执行文件
./test/game_unittest
```

### 在子目录 `cmake_build` 下，打开 Coverage 开关，构建出可执行的测试用例文件。

```shell
# Just use -DBUILD_TESTS=ON option for cmake.

rm -rf cmake_build && mkdir cmake_build && cd cmake_build && cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON .. && make
# 生成
# 执行生成的可执行文件
./test/game_unittest
```

### 在目录 `cmake_build` 下，执行 `lcov` 命令，用于解释并生成 `html` 格式的测试覆盖率报告。

运行上面打开Coverage命令之后，再运行下面的命令。

```shell
# 生成 coverage.info
cd cmake_build
lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
# 生成 out/index.html
genhtml coverage.info --output-directory out
```

## 使用 GN 和 Ninja 构建项目产物

### 构建 game_demo

```shell
rm -rf out/default && gn gen out/default && ninja -C out/default all
# 在 out/default 目录下生成可执行文件
```

上面的命令会在目录 `out/default` 下，生成两个可执行文件，分别是 `game_demo` 和 `game_unittest`。