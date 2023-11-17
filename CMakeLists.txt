




cmake_minimum_required(VERSION 3.8)
project(ssz_weixin_open_server C CXX)



# 设置tRPC-Cpp的安装位置
set(TRPC_INSTALL_PATH /usr/local/trpc-cpp/trpc)

# 加载tRPC-Cpp头文件及库路径
include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
include_directories(${INCLUDE_INSTALL_PATHS})
link_directories(${LIBRARY_INSTALL_PATHS})

# 设置proto文件桩代码生成工具的路径 - 具体使用方式见相关章节
include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)
set(PB_PROTOC ${TRPC_INSTALL_PATH}/bin/protoc)
set(TRPC_CPP_PLUGIN ${TRPC_INSTALL_PATH}/bin/trpc_cpp_plugin)

# 添加trpc库及其依赖的三方
set(LIBRARY trpc ${LIBS_BASIC})

# 在您的构建目标里link trpc库
target_link_libraries(your_cmake_target trpc)

