cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(moveCommandPlugin)

find_package(Qt5Widgets REQUIRED)

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(SOURCES_${PROJECT_NAME} MoveCommandPlugin.cpp)
set(HEADERS_${PROJECT_NAME} ClassFunctionMove.h CommandMove.h MovableAdapter.h MoveCommandPlugin.h)

message("STATUS" ${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../IoC)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLib IoC)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)


