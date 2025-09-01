cmake_minimum_required(VERSION 3.10)

project(ToDo VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Drogon
find_package(Drogon REQUIRED)

# 可执行文件
add_executable(todo main.cpp)

# 链接 Drogon 和 JsonCpp
target_link_libraries(todo PRIVATE Drogon::Drogon jsoncpp)

# 自动创建输出目录
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 根据构建类型设置输出路径
set_target_properties(todo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

