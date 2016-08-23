cmake_minimum_required(VERSION 3.6.1)
project(Core)

file(GLOB_RECURSE Core_Headers "${CORE_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE Core_Sources "${CORE_SOURCE_DIR}/*.cpp")

include_directories(${CORE_INCLUDE_DIR})
add_library(Core SHARED ${Core_Sources} ${Core_Headers})

if(WIN32)
	target_link_libraries(Core ws2_32)
elseif(UNIX)
	target_link_libraries(Core pthread)
	target_link_libraries(Core ncurses)
endif()
