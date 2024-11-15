cmake_minimum_required(VERSION 3.0)

project(TestNatSpaceBattle)

include_directories(${PROJECT_SOURCE_DIR})

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(TESTS_${PROJECT_NAME} TestCollectionCommanrMultithread.cpp TestIoCCommand.cpp TestIoCScopes.cpp TestMain.cpp TestSpaceBattle.cpp utest.cpp)

source_group ("Test Files" FILES ${TESTS_${PROJECT_NAME}})

add_subdirectory(test/googletest)
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

if(TEST_MoveCommandPlugin)
	add_subdirectory(${PROJECT_SOURCE_DIR}/TestMoveCommandPlugin)
endif()

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

add_executable(${PROJECT_NAME} ${TESTS_${PROJECT_NAME}})
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest Qt5::Gui Qt5::Core Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE IoC CommonLib natSpaceBattle_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/test/googletest/googletest/include
								 ${PROJECT_SOURCE_DIR}/test/googletest/googlemock/include
                                 ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}  ${PROJECT_SOURCE_DIR}/src/Base/jsoncpp/)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} DESTINATION .) 
