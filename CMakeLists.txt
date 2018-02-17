# cmake 版本
cmake_minimum_required(VERSION 3.9)


# 设置编编译器
SET(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/7.2.0/bin/g++-7")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# project name
project(kokola)

# settings
# set(KOKOLA_DIR ${PROJECT_SOURCE_DIR})
# SET(MYLINK test1 test2) # lib/libxx.a

# excutable path
# set(executable_output_path ${PROJECT_SOURCE_DIR}/bin)
# lib output path
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

MESSAGE("#############Start build######################")

# 当前目录文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
# 添加子项目目录 / 每个目录下需要cmake txt
ADD_SUBDIRECTORY(src/io)
ADD_SUBDIRECTORY(src/utils)

# 头文件搜索目录
INCLUDE_DIRECTORIES(include)
# 链接库搜索路径
LINK_DIRECTORIES(lib)
# 设置链接库
SET(EXTRA_LIBS ${EXTRA_LIBS} io utils)

# 生成可执行文件
ADD_EXECUTABLE(kokola ${SRC_LIST})

# 执行文件链接属性
TARGET_LINK_LIBRARIES(kokola ${EXTRA_LIBS})