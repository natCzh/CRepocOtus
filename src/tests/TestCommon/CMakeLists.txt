cmake_minimum_required(VERSION 3.0)

project(TestNatSpaceBattle)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/..)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(TESTS_${PROJECT_NAME}                  TestCollectionCommanrMultithread.cpp
TestIoCCommand.cpp  TestMain.cpp   TestSpaceBattle.cpp   TestInitObjectGame.cpp
TestCorePluginBattleCommand.cpp
#TestIoCScopes.cpp 
						  utest.cpp)

source_group ("Test Files" FILES ${TESTS_${PROJECT_NAME}})

add_subdirectory(test/googletest)
enable_testing()

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)

add_executable(${PROJECT_NAME} ${TESTS_${PROJECT_NAME}})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Gui Qt5::Core Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE natSpaceBattle_STATIC IoC_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/test/googletest/googletest/include
								 ${PROJECT_SOURCE_DIR}/test/googletest/googlemock/include
                                 ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}  ${PROJECT_SOURCE_DIR}/src/Base/jsoncpp/)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} DESTINATION .) 
