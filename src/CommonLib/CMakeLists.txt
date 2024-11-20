cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(CommonLib)

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(SOURCES_${PROJECT_NAME} CommandException.cpp)
set(HEADERS_${PROJECT_NAME} CommandException.h IPlugin.h IThreadDeque.h UObject.h UobjectException.h objectAble/IMovable.h 
                            objectAble/IRotable.h objectAble/IShotable.h IMessagable.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../IoC)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} PRIVATE IoC)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core)


