cmake_minimum_required(VERSION 3.0)
set (LIB jsoncpp)
project(${LIB} CXX)

OPTION(${LIB}_BUILD_SHARED "Build ${LIB} as shared libraries" OFF)

if (MSVC)
	# Options for Visual Studio can be added here
elseif (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fmessage-length=0")
	# TODO: enable Werror once algorithm is ready
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
	message ("Unknown compiler")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DNOMINMAX)
add_definitions(-D_USE_MATH_DEFINES)

set(LIB_SOURCES
        jsoncpp.cpp
        json.h
        utils.cpp
        utils.h
        jsonutils.h
        )

    source_group("" FILES ${LIB_SOURCES})

IF(${${LIB}_BUILD_SHARED})
    ADD_LIBRARY(${LIB} SHARED ${LIB_SOURCES})
    if(UNIX)
            set(LIB_DESTINATION lib)
    else()
            set(LIB_DESTINATION bin) # on win, put library near binary executable
    endif()
    install(TARGETS ${LIB} DESTINATION ${LIB_DESTINATION})
ELSE()
    ADD_LIBRARY(${LIB} STATIC ${LIB_SOURCES})

    if (CMAKE_VERSION VERSION_GREATER 2.8.8)
        set_property(TARGET ${LIB} PROPERTY POSITION_INDEPENDENT_CODE ON)
    elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        # add option here because POSITION_INDEPENDENT_CODE requires CMake 2.8.9
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    endif()


ENDIF()


