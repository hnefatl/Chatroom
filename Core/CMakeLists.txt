cmake_minimum_required(VERSION 3.6.1)
project(Core)

file(GLOB_RECURSE Core_Headers "${CORE_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE Core_Sources "${CORE_SOURCE_DIR}/*.cpp")

include_directories(${CORE_INCLUDE_DIR})
add_library(Core SHARED ${Core_Sources} ${Core_Headers})
include_directories(${SQL_INCLUDE_DIR})
target_link_libraries(Core Sqlite3)
target_compile_definitions(Core PUBLIC _CRT_SECURE_NO_WARNINGS)

if(WIN32)
	target_link_libraries(Core ws2_32)
elseif(UNIX)
	target_link_libraries(Core pthread)
	target_link_libraries(Core ncurses)
endif()
