cmake_minimum_required(VERSION 3.0)

project(natSpaceBattle)

OPTION (TESTINCLUDE "Including utest " ON)
OPTION (TEST_MoveCommandPlugin "Including test moveCommandPlugin" OFF)
OPTION (APP_Start " " ON)

include_directories(${PROJECT_SOURCE_DIR}/)
add_definitions(-D_USE_MATH_DEFINES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC version ${gRPC_VERSION}")

#TODO переделать это!!
FILE(GLOB_RECURSE HEADERS mainServer/MainServerCorePluginBattleCommand.h Command/*.h Common/*.h EndPoint/*.h Exception/*.h IoC/*.h
                          RegisterCommand/*.h Scopes/*.h service/*.h service/TourneyService/*.h 
                          inputPlugins/CommandInterpretMoveStopRotateShot/*.h)

FILE(GLOB_RECURSE SOURCES main.cpp mainServer/MainServerCorePluginBattleCommand.cpp Scopes/*.cpp service/*.cpp service/TourneyService/*.cpp Command/*.cpp Common/*.cpp inputPlugins/CommandInterpretMoveStopRotateShot/*.cpp)

set(PROTOC mainServer/router_serverGame.grpc.pb.h mainServer/router_serverGame.pb.h mainServer/router_serverGame.grpc.pb.cc mainServer/router_serverGame.pb.cc)

source_group ("Source Files" FILES ${SOURCES})
source_group ("Header Files" FILES ${HEADERS})
source_group ("Protoc Files" FILES ${PROTOC})

if(TARGET protobuf::protoc)
    get_target_property(PROTO_COMPILER protobuf::protoc "LOCATION_${CMAKE_BUILD_TYPE}")
    get_target_property(PROTOBUF_LIBS protobuf::libprotobuf "LOCATION_${CMAKE_BUILD_TYPE}")
    get_target_property(PROTOBUF_INCLUDE protobuf::libprotobuf INTERFACE_INCLUDE_DIRECTORIES)
    set(GRPC_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

set(PROTO_HDR)
set(PROTO_SRC)
set(GRPC_HDR)
set(GRPC_SRC)

add_subdirectory(${PROJECT_SOURCE_DIR}/Base/jsoncpp/)
add_subdirectory(${PROJECT_SOURCE_DIR}/IoC/)
add_subdirectory(${PROJECT_SOURCE_DIR}/CommonLib/)
#if(NOT TESTINCLUDE)
    add_subdirectory(${PROJECT_SOURCE_DIR}/inputPlugins/)
#endif()

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)

#add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${PROTOC})
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${PROTOC})
target_link_libraries(${PROJECT_NAME} PRIVATE IoC CommonLib)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets protobuf::libprotobuf gRPC::grpc++)

if(TESTINCLUDE)
        add_library(${PROJECT_NAME}_STATIC STATIC ${SOURCES} ${HEADERS} ${PROTOC})
        target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE IoC_STATIC CommonLib)
	set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 17
                                                            CXX_STANDARD_REQUIRED ON)
	target_include_directories(${PROJECT_NAME}_STATIC PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets protobuf::libprotobuf gRPC::grpc++)
endif()

if(TESTINCLUDE)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests/TestCommon)
endif()

if(APP_Start)
    add_executable(${PROJECT_NAME}_APP ${SOURCES} ${HEADERS} ${PROTOC})
    #add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${PROTOC})
    target_link_libraries(${PROJECT_NAME}_APP PRIVATE IoC CommonLib)
    set_target_properties(${PROJECT_NAME}_APP PROPERTIES CXX_STANDARD 17
                                          CXX_STANDARD_REQUIRED ON)
    target_include_directories(${PROJECT_NAME}_APP PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_APP PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets protobuf::libprotobuf gRPC::grpc++)
endif()

message(STATUS "root prefix path = ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(TARGETS ${PROJECT_NAME}_APP DESTINATION .)
 
      
