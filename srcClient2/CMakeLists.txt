cmake_minimum_required(VERSION 3.0)

project(clientQt)

OPTION (TESTINCLUDE "Including utest " OFF)
OPTION (APP_Start " " ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${PROJECT_SOURCE_DIR}/)
add_definitions(-D_USE_MATH_DEFINES)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC version ${gRPC_VERSION}")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

#TODO переделать это!!
set(HEADERS ClientPaintClass.h FieldGame/FieldGame.h GuiClient.h LoggerVisitor.h CustomLog/CustomLog.h CustomLog/MessageType.h)

set(SOURCES main.cpp ClientPaintClass.cpp FieldGame/FieldGame.cpp GuiClient.cpp CustomLog/CustomLog.cpp)

set(PROTOC protoFile/client_router.grpc.pb.cc protoFile/client_router.pb.cc protoFile/client_router.grpc.pb.h protoFile/client_router.pb.h)

add_subdirectory(Logger)

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

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${PROTOC})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotobuf gRPC::grpc++ Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Logger)

if(TESTINCLUDE)
	add_library(${PROJECT_NAME}_STATIC STATIC ${SOURCES} ${HEADERS} ${PROTOC})
	set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 17
                                                            CXX_STANDARD_REQUIRED ON)
        target_include_directories(${PROJECT_NAME}_STATIC PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE gRPC::grpc++ protobuf::libprotobuf gRPC::grpc Qt5::Core)
        target_link_libraries(${PROJECT_NAME}_STATIC PRIVATE Logger)
endif()

if(APP_Start)
    add_executable(${PROJECT_NAME}_APP ${HEADERS} ${SOURCES} ${PROTOC})
    set_target_properties(${PROJECT_NAME}_APP PROPERTIES CXX_STANDARD 17
                                          CXX_STANDARD_REQUIRED ON)
    target_include_directories(${PROJECT_NAME}_APP PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_APP PRIVATE protobuf::libprotobuf gRPC::grpc++ Qt5::Core)
    target_link_libraries(${PROJECT_NAME}_APP PRIVATE Logger)
endif()

if(TESTINCLUDE)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

 
      
