cmake_minimum_required(VERSION 3.0)

project(unittest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BUILD_GMOCK OFF CACHE BOOL "Build only gtest")
if (MSVC)
	set(gtest_force_shared_crt ON CACHE BOOL "Use shared C RunTime")
#	message("gtest_force_shared_crt  = ${gtest_force_shared_crt}")
endif()

add_subdirectory(googletest)

