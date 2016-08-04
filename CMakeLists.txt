cmake_minimum_required(VERSION 3.6.1)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


set(CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Core/include)
set(CORE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Core/src)

set(CLIENT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Client/include)
set(CLIENT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Client/src)

set(SERVER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Server/include)
set(SERVER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Server/src)


add_subdirectory(Core)
add_subdirectory(Client)
add_subdirectory(Server)
