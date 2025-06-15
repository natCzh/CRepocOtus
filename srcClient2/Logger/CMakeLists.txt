cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

if (CMAKE_VERSION VERSION_GREATER 2.8.10)
	cmake_policy(SET CMP0020 NEW)
endif()

set(PROJECT Logger)
project(${PROJECT} CXX)

OPTION(VLD_USING "Build ${PROJECT} with vld analize" OFF)

if(VLD_USING)
    include(CMakeUserFindVLD.cmake)
    if(VLD_FOUND)
        add_definitions(-DVLD_FOUND)
        include_directories(${VLD_INCLUDE_DIR})
        link_directories(${VLD_LIB_DIR})
        message("VLD_LIB_DIR: ${VLD_LIB_DIR}")
    endif()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(BIN_DESTINATION bin)
    set(RES_DESTINATION bin)
    set(LIB_DESTINATION lib)
    set(DOC_DESTINATION doc)
    set(INC_DESTINATION include)
    set(CMAKE_CONFIG_DESTINATION cmake)
else()
    set(BIN_DESTINATION usr/bin)
    set(RES_DESTINATION usr/share/${PROJECT})
    set(LIB_DESTINATION usr/lib)
    set(DOC_DESTINATION ${RES_DESTINATION}/doc)
    set(INC_DESTINATION ${RES_DESTINATION}/include)
    set(CMAKE_CONFIG_DESTINATION ${RES_DESTINATION}/cmake)
endif()

IF (WIN32)
    add_definitions(-DWIN32)
ELSEIF(UNIX)
    add_definitions(-DUNIX)
    add_definitions (-DLINUX)
ENDIF()

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

OPTION(LOGGER_BUILD_SHARED "Build ${PROJECT} shared" OFF)

if(LOGGER_BUILD_SHARED)
    add_definitions(-DLOGGER_BUILD_SHARED)
endif()

add_definitions(-DLOGGER_LIBRARY)
add_definitions(-DNOMINMAX)
add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DUSE_PCH)
add_definitions(-D_USE_SHORT_CONTEXT_)

find_package (Qt5Core)
find_package (Qt5Gui)
find_package (Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(OpenMP)
if(OPENMP_FOUND)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if (MSVC)
#	set(CMAKE_DEBUG_POSTFIX "d")
#	add_definitions (/W4)
	add_definitions (/Oi)
	add_definitions(-D_WIN32)
#	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
#	add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
elseif (CMAKE_COMPILER_IS_GNUCXX)

        set(GCC_BLACKLIST
                4.7.0
                4.7.1)
        foreach(BAD_GCC_VER ${GCC_BLACKLIST})
                if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL ${BAD_GCC_VER})
                        message(FATAL_ERROR "Unsupported GCC version ${CMAKE_CXX_COMPILER_VERSION}, "
                                "see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=54172" )
                endif()
        endforeach()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -pedantic -Wno-long-long -fmessage-length=0")
	# "reorder" warning happens often in header files which produces too much garbage in build log
	# let's just avoid this type of errors in our code.
	# "no return statement in function returning non-void" (return-type) is almost always a bug.
	# Once all types of warnings are fixed, "-Werror" should be enabled to avoid possible future problems in code.
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type -Werror=reorder")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	# Options for Intel compiler can be added here
else ()
	message ("Unknown compiler")
endif ()




SET(Project_sources
	logger.cpp
)

SET(Project_headers
	logger_global.h
	logger.h
)

set (TESTS_FILES
        #Tests/Serialization.cxx
)

source_group ("Headers" FILES ${Project_headers})
source_group ("Sources" FILES ${Project_sources})
source_group ("Tests Files" FILES ${TESTS_FILES})

include_directories (${PROJECT_SOURCE_DIR}) 
include_directories (${PROJECT_BINARY_DIR}) 

if(LOGGER_BUILD_SHARED)
    add_library(${PROJECT} SHARED ${Project_sources} ${Project_headers})
else()
    add_library(${PROJECT} STATIC ${Project_sources} ${Project_headers})
endif()


set(LIBS Qt5::Core Qt5::Gui Qt5::Widgets)
if(VLD_FOUND)
    set(LIBS ${LIBS} vld)
endif()

target_link_libraries (${PROJECT} LINK_PRIVATE ${LIBS})

if (CMAKE_VERSION VERSION_GREATER 2.8.8)
        set_property(TARGET ${PROJECT} PROPERTY POSITION_INDEPENDENT_CODE ON)
elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
# add option here because POSITION_INDEPENDENT_CODE requires CMake 2.8.9
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()

#option(LOGGER_BUILD_TESTS "Build logger tests as separate executable" ON)

if (LOGGER_BUILD_TESTS)
        enable_testing()
        add_definitions(-DINCLUDE_UNITTESTS)

        string(REPLACE "-pedantic" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

        if (CMAKE_VERSION VERSION_GREATER 2.8.8)
                set_property(TARGET ${PROJECT} PROPERTY POSITION_INDEPENDENT_CODE ON)
        elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        # add option here because POSITION_INDEPENDENT_CODE requires CMake 2.8.9
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
        endif()

        find_package (Qt5Core)

        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTOUIC ON)

        if(NOT TARGET UnitTest++)
                add_subdirectory(unittest-cpp)
        endif()
        add_executable(test_${PROJECT}
                test.cpp
                ${TESTS_FILES}
        )
        target_link_libraries(test_${PROJECT} ${PROJECT} ${LIBS} UnitTest++)

        add_test(
                NAME ${PROJECT}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND test_${PROJECT}
        )
        set_tests_properties(${LIB} PROPERTIES TIMEOUT 60)
endif()




if(WIN32)
	if(CMAKE_BUILD_TYPE MATCHES Debug)
		install(FILES ${QTDIR}/bin/Qt5Cored.dll DESTINATION ${BIN_DESTINATION})
	    install(FILES ${QTDIR}/bin/Qt5Guid.dll DESTINATION ${BIN_DESTINATION})
		install(FILES ${QTDIR}/bin/Qt5Widgetsd.dll DESTINATION ${BIN_DESTINATION})
		install(FILES ${QTDIR}/plugins/platforms/qwindowsd.dll DESTINATION ${BIN_DESTINATION}/platforms)
	else()
		install(FILES ${QTDIR}/bin/Qt5Core.dll DESTINATION ${BIN_DESTINATION})
	    install(FILES ${QTDIR}/bin/Qt5Gui.dll DESTINATION ${BIN_DESTINATION})
		install(FILES ${QTDIR}/bin/Qt5Widgets.dll DESTINATION ${BIN_DESTINATION})
		install(FILES ${QTDIR}/plugins/platforms/qwindows.dll DESTINATION ${BIN_DESTINATION}/platforms)
	endif()

endif()

install(TARGETS ${PROJECT} 
		RUNTIME DESTINATION ${BIN_DESTINATION}
		ARCHIVE DESTINATION ${LIB_DESTINATION}
		LIBRARY DESTINATION ${LIB_DESTINATION}
		COMPONENT library
		)


# CPack-related
set(CPACK_PACKAGE_CONTACT "Aleksandr Nikolaev <anikolaev@stc-spb.ru>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Qt logger.")
set(CPACK_PACKAGE_VENDOR "STC")

set (CPACK_PACKAGE_NAME ${PROJECT})
if (NOT DEFINED CPACK_PACKAGE_VERSION)
        set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
endif()

if (UNIX)
        set (CPACK_GENERATOR "TBZ2;DEB")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libgcc1, libqt5core5a, libqt5gui5")
        set (CPACK_STRIP_FILES ON)
        set (CMAKE_INSTALL_PREFIX "/")
        exec_program(dpkg
                ARGS --print-architecture
                OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
        set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

        set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
            "${CMAKE_CURRENT_SOURCE_DIR}/postinst")

else()
        set (CPACK_GENERATOR "ZIP" )
        #check if NSIS (Nullsoft Scriptable Install System) installed
        find_program(NSIS_PROGRAM makensis.exe
                PATHS
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\NSIS;InstallLocation]"
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\NSIS;InstallLocation]")
        if(NSIS_PROGRAM)
                set (CPACK_GENERATOR "${CPACK_GENERATOR};NSIS")
        endif()
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(CPACK_SYSTEM_NAME win64)
        else()
                set(CPACK_SYSTEM_NAME win32)
        endif()
        set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_SYSTEM_NAME}")
endif()
set (CPACK_PACKAGING_INSTALL_PREFIX "/")
include(CPack)
