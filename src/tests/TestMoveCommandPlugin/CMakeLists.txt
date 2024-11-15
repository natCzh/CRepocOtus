cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(testMoveCommandPlugin LANGUAGES CXX C)

# GTest
add_subdirectory(${PROJECT_SOURCE_DIR}/../../test/googletest)
enable_testing()

set(TESTS_PROJECT_FILES utest.cpp TestMoveCommandPlugin.cpp)

add_executable(${PROJECT_NAME} ${TESTS_PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest)
target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/gtest-1.10/googletest/include ${PROJECT_SOURCE_DIR}/gtest-1.10/googlemock/include)
target_link_libraries(${PROJECT_NAME} PRIVATE moveCommandPlugin_STATIC)
