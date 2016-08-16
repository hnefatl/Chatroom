cmake_minimum_required(VERSION 3.6.1)
project(KeyIdentifier)

add_executable(KeyIdentifier main.cpp)
include_directories(${CORE_INCLUDE_DIR})
target_link_libraries(KeyIdentifier Core)
