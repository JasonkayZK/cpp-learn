cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)

# 单个目录下，同时编译多个文件-1
# 同时在一个add_executable中声明
#add_executable(cpp_learn main.cpp MathUtils.cpp MathUtils.h)

# 单个目录下，同时编译多个文件-2
# 查找当前目录下所有源文件
# 并将名称保存到DIR_SRCS变量中
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(cpp_learn ${DIR_SRCS})
