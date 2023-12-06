# copyright 2023-11-18 skylanwei

cmake_minimum_required(VERSION 3.14)
project(trpc_template_server C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FetchContent)
set(TRPC_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/framework/trpc-cpp/)
set(TRPC_CPP_GIT_URL https://github.com/city-invoker/trpc-cpp.git)
set(TRPC_CPP_GIT_TAG v1.0.0)
FetchContent_Declare(
    trpc-cpp
    GIT_REPOSITORY        ${TRPC_CPP_GIT_URL}
    GIT_TAG               ${TRPC_CPP_GIT_TAG}
    SOURCE_DIR            ${TRPC_ROOT_PATH}
)

set(OPTL_GIT_URL https://github.com/city-invoker/cpp-telemetry-opentelemetry.git)
set(OPTL_GIT_TAG v1.0.0)
FetchContent_Declare(
    cpp-telemetry-opentelemetry
    GIT_REPOSITORY        ${OPTL_GIT_URL}
    GIT_TAG               ${OPTL_GIT_TAG}
    SOURCE_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/plugin/cpp-telemetry-opentelemetry/
)

set(PROTOS_GIT_URL https://github.com/city-invoker/protos.git)
set(PROTOS_GIT_TAG dev_version_1.0.0)
FetchContent_Declare(
    protos 
    GIT_REPOSITORY        ${PROTOS_GIT_URL}
    GIT_TAG               ${PROTOS_GIT_TAG}
    SOURCE_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/protos/
)

set(COMMON_GIT_URL https://github.com/city-invoker/common.git)
set(COMMON_GIT_TAG dev_version_1.0.0)
FetchContent_Declare(
    common 
    GIT_REPOSITORY        ${COMMON_GIT_URL}
    GIT_TAG               ${COMMON_GIT_TAG}
    SOURCE_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/common/
)

message("fetch content trpc-cpp cpp-telemetry-opentelemetry protos common from git....")
FetchContent_MakeAvailable(trpc-cpp cpp-telemetry-opentelemetry protos common)

include(${TRPC_ROOT_PATH}/cmake/config/trpc_config.cmake)
include(${TRPC_ROOT_PATH}/cmake/tools/trpc_utils.cmake)

# target *.cc
set(TARGET trpc_template_server)
file(GLOB_RECURSE SRC_FILES . *.cc *.cpp *.hpp)
file(GLOB_RECURSE TEST_FILES . *test.cc *test.cpp *testing.cc)
list(REMOVE_ITEM SRC_FILES ${TEST_FILES})

list(REMOVE_DUPLICATES ${CMAKE_CXX_FLAGS})
list(SORT ${CMAKE_CXX_FLAGS})

add_executable(${TARGET} ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_PATHS})

## linking
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")
set(TARGET_LINK_PATHS ${TARGET_LINK_PATHS} ${LIBRARY_PATHS})
target_link_directories(${TARGET} PUBLIC ${TARGET_LINK_PATHS})

set(TARGET_LINK_LIBS ${TARGET_LINK_LIBS}
  trpc
  trpc_cpp_plugin_telemetry_opentelemetry 
  trpc_opentelemetry_proto
  ${LIB_METRICS_PROMETHEUS})

target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})


