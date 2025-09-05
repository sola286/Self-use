cmake_minimum_required(VERSION 3.10)
project(ToDo VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 如果 Drogon 安装在非标准路径，指定路径
# set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/Drogon")

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)

# 添加 include 路径
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

file(GLOB_RECURSE HDR_FILES 
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

add_executable(todo ${SRC_FILES})

target_link_libraries(todo PRIVATE Drogon::Drogon jsoncpp_lib pthread ssl crypto dl z)

set_target_properties(todo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

