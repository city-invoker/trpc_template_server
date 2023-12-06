# copyright 2023-11-18 skylanwei

cmake_minimum_required(VERSION 3.14)
project(trpc_template_server C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

## include *.h
#set(TRPC_INSTALL_PATH /usr/local/trpc-cpp/trpc)
#include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
#include_directories(${INCLUDE_INSTALL_PATHS})
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/protos/")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common/include/")

## lib directories
#link_directories(${LIBRARY_INSTALL_PATHS})
#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/")

# target *.cc
set(TARGET trpc_template_server)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/protos/" PB_SRCS)
add_executable(${TARGET} ${PB_SRCS} ${SRCS})

# linking
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set(LIBRARY trpc ${LIBS_BASIC} trpc_cpp_plugin_telemetry_opentelemetry trpc_opentelemetry_proto)
target_link_libraries(${TARGET} ${LIBRARY})


