cmake_minimum_required(VERSION 3.10)

project(Trie)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找必要的库
find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

# 定义主可执行文件
add_executable(main
        Main.cpp
        trie.cpp
        trie_store.cpp
)

# 包含头文件目录
target_include_directories(main PRIVATE
        ${CMAKE_SOURCE_DIR}
)

# 链接 Google Test 和 fmt 库
target_link_libraries(main PRIVATE
        GTest::GTest
        GTest::Main
        fmt::fmt
)

# 启用测试
enable_testing()

# 自动发现所有 Google Test 测试
include(GoogleTest)
gtest_discover_tests(main)

# 你可以通过 CTest 来运行所有的测试
