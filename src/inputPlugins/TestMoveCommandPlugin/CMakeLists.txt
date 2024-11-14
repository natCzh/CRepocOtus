cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(testMoveCommandPlugin LANGUAGES CXX C)

# GTest
add_subdirectory(${PROJECT_SOURCE_DIR}/../../../test/googletest)
enable_testing()

set(TESTS_PROJECT_FILES utest.cpp)

add_executable(${PROJECT_NAME} ${TESTS_PROJECT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE )
target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/emulator
												   ${PROJECT_SOURCE_DIR}/../include 
												   ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} 
												   ${PROJECT_SOURCE_DIR}/gtest-1.10/googletest/include ${PROJECT_SOURCE_DIR}/gtest-1.10/googlemock/include
                                                   ${PROJECT_SOURCE_DIR}/../storage 
                                                   ${PROJECT_SOURCE_DIR}/../routines ${PROJECT_SOURCE_DIR}/../routines/detector ${PROJECT_SOURCE_DIR}/../routines/tracker ${PROJECT_SOURCE_DIR}/../routines/simple
                                                   ${PROJECT_SOURCE_DIR}/../Base/jsoncpp ${PROJECT_SOURCE_DIR}/../config 
                                                   ${PROJECT_SOURCE_DIR}/../modules ${PROJECT_SOURCE_DIR}/../modules/reader
                                                   ${PROJECT_SOURCE_DIR}/../wrappers
                                                   ${PROJECT_SOURCE_DIR}/simpleInterface)

#	if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#	    target_link_libraries                     (utest                      debug
#    	${CMAKE_CURRENT_BINARY_DIR}/lib/gtest-1.7.0/Debug/gmock.lib debug ${CMAKE_CURRENT_BINARY_DIR}/lib/gtest-1.7.0/gtest/Debug/gtest.lib)
#	    target_link_libraries (utest optimized ${CMAKE_CURRENT_BINARY_DIR}/lib/gtest-1.7.0/Release/gmock.lib optimized ${CMAKE_CURRENT_BINARY_DIR}/lib/gtest-1.7.0/gtest/Release/gtest.lib)
#	else ()
#		target_link_libraries (utest -ldl gmock)   
#	endif ()