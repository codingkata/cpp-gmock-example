
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


## 解析增量覆盖率

从lcov命令生成的每个源文件对应的"xxx.gov.html" 文件中解释出两次提交（commit A 和 commit B)之间的增量行覆盖率。

假设:

1. 所以的 gov.html 文件都放在一个名为 `coverage` 的目录
2. 源代码在当前目录下的 src 目录下
3. 两次commit id 分别是 `9834e86` 和`acb497f`，
4. 增量的覆盖率阈值是 60%

则，对应的命令如下：

```shell
 python3 my_lcov.py "9834e86..acb497f" '["src"]' "coverage" 0.6
```

