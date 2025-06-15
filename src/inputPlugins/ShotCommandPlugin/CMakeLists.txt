cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(shotCommandPlugin)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

add_definitions(-D_USE_MATH_DEFINES)

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(SOURCES_${PROJECT_NAME} ShotCommandPlugin.cpp)
set(HEADERS_${PROJECT_NAME} ClassFunctionShot.h CommandShot.h ShotAdapter.h ShotCommandPlugin.h IShotableSetNumberShotClass.h IShotableSetShotActClass.h)

message("STATUS" ${PROJECT_SOURCE_DIR})
message("STATUS" !!!!!!!!!!!!!!!!!!!)

add_library(${PROJECT_NAME} SHARED ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../ ../../CommonLib ../../Exception)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DPLUGIN_LIBRARY)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLib IoC)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)
message(STATUS "plugin prefix path = ${CMAKE_INSTALL_PREFIX}")

install(TARGETS ${PROJECT_NAME} DESTINATION plugins)