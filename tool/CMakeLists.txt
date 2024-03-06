# Copyright 2023-11-09 skylanwei 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.8)
project(trpc_cli C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

# 设置tRPC-Cpp的安装位置
set(TRPC_INSTALL_PATH "/usr/local/trpc-cpp/trpc")

## 加载tRPC-Cpp头文件及库路径
include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
#include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)
include_directories("${TRPC_INSTALL_PATH}/include/")


#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/protos/*.cc)

set(TARGET trpc_cli)

add_executable(${TARGET} trpc_cli.cc)
target_include_directories(${TARGET} PUBLIC ${INCLUDE_PATHS})

## linking
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")
find_library(LIBPROTO libtrpc_proto.a "${CMAKE_CURRENT_SOURCE_DIR}/../protos/lib/")
set(TARGET_LINK_PATHS ${TARGET_LINK_PATHS} "${TRPC_INSTALL_PATH}/lib")
target_link_directories(${TARGET} PUBLIC ${TARGET_LINK_PATHS})
set(TARGET_LINK_LIBS ${LIBS_BASIC} trpc ${LIBPROTO})

target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})

