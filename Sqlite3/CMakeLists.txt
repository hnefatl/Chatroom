cmake_minimum_required(VERSION 3.6.1)
project(Sqlite3)

file(GLOB_RECURSE Sqlite3_Headers "${SQL_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE Sqlite3_Sources "${SQL_SOURCE_DIR}/*.c")

add_library(Sqlite3 STATIC ${Sqlite3_Sources} ${Sqlite3_Headers})
set_property(TARGET Sqlite3 PROPERTY POSITION_INDEPENDENT_CODE ON)
if (UNIX)
	target_link_libraries(Sqlite3 dl)
endif()
