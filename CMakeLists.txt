cmake_minimum_required(VERSION 3.0)

project(natSpaceBattle)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(src/)
add_definitions(-D_USE_MATH_DEFINES)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

#TODO переделать это!!
FILE(GLOB_RECURSE HEADERS src/Command/*.h src/Common/*.h src/EndPoint/*.h src/Exception/*.h src/IoC/*.h 
                          src/RegisterCommand/*.h src/Scopes/*.h src/service/*.h)

FILE(GLOB_RECURSE SOURCES src/Scopes/*.cpp src/service/*.cpp src/service/*.cpp)

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

add_subdirectory(${PROJECT_SOURCE_DIR}/src/Base/jsoncpp/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/IoC/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/CommonLib/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/inputPlugins/)

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${TESTS_PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest Qt5::Gui Qt5::Core Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE IoC CommonLib)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/test/googletest/googletest/include
								 ${PROJECT_SOURCE_DIR}/test/googletest/googlemock/include
                                 ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}  ${PROJECT_SOURCE_DIR}/src/Base/jsoncpp/)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

message(STATUS "root prefix path = ${CMAKE_INSTALL_PREFIX}")


install(TARGETS ${PROJECT_NAME} DESTINATION .)

 
