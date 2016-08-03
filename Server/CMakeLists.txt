cmake_minimum_required(VERSION 3.6.1)
project(Server)

file(GLOB_RECURSE Server_Headers "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE Server_Sources "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${SERVER_INCLUDE_DIR})
add_executable(Server ${Server_Sources} ${Server_Headers})

include_directories(${CORE_INCLUDE_DIR})
target_link_libraries(Server Core)
