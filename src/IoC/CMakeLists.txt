cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(IoC LANGUAGES CXX C)

set(SOURCES_${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.cpp )
set(HEADERS_${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/IoC.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/RegisterDependencyCommand.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/SetCurrentScopeCommand.h  
                            ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IDependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IdScope.h
                            ${PROJECT_SOURCE_DIR}/Scopes/Scope.h)

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

add_library(${PROJECT_NAME} STATIC ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

