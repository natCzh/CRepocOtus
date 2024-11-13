cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(rotateCommandPlugin LANGUAGES CXX C)

set(SOURCES_${PROJECT_NAME} RotateCommandPlugin.cpp)
set(HEADERS_${PROJECT_NAME} ClassFunctionRotate.h CommandRotate.h RotableAdapter.h RotateCommandPlugin.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../Common/objectAble ${PROJECT_SOURCE_DIR}/../IoC)


