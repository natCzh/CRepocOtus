cmake_minimum_required(VERSION 3.0)

project(natSpaceBattle)

OPTION (TESTINCLUDE "Including utest " ON)
OPTION (TEST_MoveCommandPlugin "Including test moveCommandPlugin" OFF)

include_directories(${PROJECT_SOURCE_DIR}/)
add_definitions(-D_USE_MATH_DEFINES)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

#TODO переделать это!!
FILE(GLOB_RECURSE HEADERS Command/*.h Common/*.h EndPoint/*.h Exception/*.h IoC/*.h 
                          RegisterCommand/*.h Scopes/*.h service/*.h service/TourneyService/*.h 
                          inputPlugins/CommandInterpretMoveStopRotateShot/*.h)

FILE(GLOB_RECURSE SOURCES Scopes/*.cpp service/*.cpp service/TourneyService/*.cpp Command/*.cpp inputPlugins/CommandInterpretMoveStopRotateShot/*.cpp)

source_group ("Source Files" FILES ${SOURCES})
source_group ("Header Files" FILES ${HEADERS})

add_subdirectory(${PROJECT_SOURCE_DIR}/Base/jsoncpp/)
add_subdirectory(${PROJECT_SOURCE_DIR}/IoC/)
add_subdirectory(${PROJECT_SOURCE_DIR}/CommonLib/)
if(NOT TESTINCLUDE)
    add_subdirectory(${PROJECT_SOURCE_DIR}/inputPlugins/)
endif()

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE IoC CommonLib)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets)

if(TESTINCLUDE)

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

	add_library(${PROJECT_NAME}_STATIC STATIC ${SOURCES} ${HEADERS})
        target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE IoC_STATIC CommonLib)
	set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 17
                                                            CXX_STANDARD_REQUIRED ON)
	target_include_directories(${PROJECT_NAME}_STATIC PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets)
endif()

message(STATUS "root prefix path = ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} DESTINATION .)

if(TESTINCLUDE)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests/TestCommon)
endif()



 
      
