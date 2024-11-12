cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(IoC)

include_directories(${PROJECT_SOURCE_DIR})

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(SOURCES_${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.cpp  ${PROJECT_SOURCE_DIR}/Scopes/IdScope.cpp)
set(HEADERS_${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/IoC.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/RegisterDependencyCommand.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/SetCurrentScopeCommand.h  
                            ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IDependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IdScope.h
                            ${PROJECT_SOURCE_DIR}/Scopes/Scope.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)

