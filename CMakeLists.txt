cmake_minimum_required(VERSION 3.0)

project(natSpaceBattle)

include_directories(/)
include_directories(src/)

#TODO переделать это!!!
FILE(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h )

FILE(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

FILE(GLOB_RECURSE TESTS_PROJECT_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

source_group ("Source Files" FILES ${SOURCES})
source_group ("Header Files" FILES ${HEADERS})
source_group ("Test Files" FILES ${TESTS_PROJECT_FILES})

add_subdirectory(${PROJECT_SOURCE_DIR}/test/googletest)
enable_testing()

if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()
    # Set compiler options.
    set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    if(${MSVC_RUNTIME} STREQUAL "static")
      message(STATUS
        "MSVC -> forcing use of statically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
      endforeach()
    else()
      message(STATUS
        "MSVC -> forcing use of dynamically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()
      endforeach()
    endif()
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${TESTS_PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/test/googletest/googletest/include
								 ${PROJECT_SOURCE_DIR}/test/googletest/googlemock/include
								 ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

 
