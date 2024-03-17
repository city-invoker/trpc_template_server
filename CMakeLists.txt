# copyright 2023-11-18 skylanwei

cmake_minimum_required(VERSION 3.14)
project(trpc_template_server C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare -Wno-error=maybe-uninitialized")

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

set(TARGET_LINK_LIBS trpc ${LIBS_BASIC})

target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})


