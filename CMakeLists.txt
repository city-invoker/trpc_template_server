# copyright 2023-11-18 skylanwei

cmake_minimum_required(VERSION 3.14)
project(trpc_template_server C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

#include(FetchContent)
#set(TRPC_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/framework/trpc-cpp/)
#set(TRPC_CPP_GIT_URL https://github.com/city-invoker/trpc-cpp.git)
#set(TRPC_CPP_GIT_TAG v1.0.0)
#FetchContent_Declare(
#    trpc-cpp
#    GIT_REPOSITORY        ${TRPC_CPP_GIT_URL}
#    GIT_TAG               ${TRPC_CPP_GIT_TAG}
#    SOURCE_DIR            ${TRPC_ROOT_PATH}
#)

#set(OPTL_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/plugins/cpp-telemetry-opentelemetry/)
#set(OPTL_GIT_URL https://github.com/city-invoker/cpp-telemetry-opentelemetry.git)
#set(OPTL_GIT_TAG v1.0.0)
#FetchContent_Declare(
#    cpp-telemetry-opentelemetry
#    GIT_REPOSITORY        ${OPTL_GIT_URL}
#    GIT_TAG               ${OPTL_GIT_TAG}
#    SOURCE_DIR            ${OPTL_ROOT_PATH} 
#)

#set(PROTOS_GIT_URL https://github.com/city-invoker/protos.git)
#set(PROTOS_GIT_TAG dev_version_1.0.0)
#FetchContent_Declare(
#    protos 
#    GIT_REPOSITORY        ${PROTOS_GIT_URL}
#    GIT_TAG               ${PROTOS_GIT_TAG}
#    SOURCE_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/protos/
#)
#
#set(COMMON_GIT_URL https://github.com/city-invoker/common.git)
#set(COMMON_GIT_TAG dev_version_1.0.0)
#FetchContent_Declare(
#    common 
#    GIT_REPOSITORY        ${COMMON_GIT_URL}
#    GIT_TAG               ${COMMON_GIT_TAG}
#    SOURCE_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/common/
#)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare -Wno-error=maybe-uninitialized")

#if (NOT trpc-cpp_POPULATED)
#  message("fetch content and make available trpc-cpp from git...")
#  FetchContent_MakeAvailable(trpc-cpp)
#endif()

#if (NOT cpp-telemetry-opentelemetry_POPULATED)
#  message("fetch content and make available cpp-telemetry-opentelemetry from git...")
#  FetchContent_MakeAvailable(cpp-telemetry-opentelemetry)
#endif()

#if (NOT protos_POPULATED)
#  message("fetch content and make available protos from git...")
#  FetchContent_MakeAvailable(protos)
#endif()
#
#if (NOT common_POPULATED)
#  message("fetch content and make available common from git...")
#  FetchContent_MakeAvailable(common)
#endif()

set(TRPC_INSTALL_PATH "/usr/local/trpc-cpp/trpc")
set(TRPC_INCLUDE_PATHS "${TRPC_INSTALL_PATH}/include/")

include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)

# target *.cc
set(TARGET trpc_template_server)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cc
                            ${CMAKE_CURRENT_SOURCE_DIR}/protos/*.cc
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
                            ${CMAKE_CURRENT_SOURCE_DIR}/trpc_template_server.cc
                            ${CMAKE_CURRENT_SOURCE_DIR}/trpc_template_service.cc
                            )
file(GLOB_RECURSE TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*test.cc
                             ${CMAKE_CURRENT_SOURCE_DIR}/protos/*test.cc
                             ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cc
                             )
list(REMOVE_ITEM SRC_FILES ${TEST_FILES})
add_executable(${TARGET} ${SRC_FILES})

target_include_directories(${TARGET} PUBLIC ${TRPC_INCLUDE_PATHS})

## linking
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/")
target_link_directories(${TARGET} PUBLIC "${TRPC_INSTALL_PATH}/lib/")

set(TARGET_LINK_LIBS trpc ${LIBS_BASIC}
  #trpc_cpp_plugin_telemetry_opentelemetry 
  #trpc_opentelemetry_proto
  )

target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})


