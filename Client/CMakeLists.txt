cmake_minimum_required(VERSION 3.6.1)
project(Client)

file(GLOB_RECURSE Client_Headers "${CLIENT_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE Client_Sources "${CLIENT_SOURCE_DIR}/*.cpp")

include_directories(${CLIENT_INCLUDE_DIR})
add_executable(Client ${Client_Sources} ${Client_Headers})
include_directories(${CORE_INCLUDE_DIR})
target_link_libraries(Client Core)
