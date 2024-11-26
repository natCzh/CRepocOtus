cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(IoC)

include_directories(${PROJECT_SOURCE_DIR})

# //////////////// Boost
find_package(Boost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(SOURCES_${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.cpp  ${PROJECT_SOURCE_DIR}/Scopes/IdScope.cpp)
set(HEADERS_${PROJECT_NAME} IoC.h IoCException.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/RegisterDependencyCommand.h ${PROJECT_SOURCE_DIR}/Scopes/CommandsScope/SetCurrentScopeCommand.h  
                            ${PROJECT_SOURCE_DIR}/Scopes/DependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IDependencyResolve.h ${PROJECT_SOURCE_DIR}/Scopes/IdScope.h
                            ${PROJECT_SOURCE_DIR}/Scopes/Scope.h)







add_library(${PROJECT_NAME} ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17
                                      CXX_STANDARD_REQUIRED ON)



if(TESTINCLUDE)

      if(MSVC)
          # Default to statically-linked runtime.
          if("${MSVC_RUNTIME}" STREQUAL "")
            set(MSVC_RUNTIME "static")
          endif()
          # Set compiler options.
          set(variables
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
          )
          if(${MSVC_RUNTIME} STREQUAL "static")
            message(STATUS
              "MSVC -> forcing use of statically-linked runtime."
            )
            foreach(variable ${variables})
              if(${variable} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
              endif()
            endforeach()
          else()
            message(STATUS
              "MSVC -> forcing use of dynamically-linked runtime."
            )
            foreach(variable ${variables})
              if(${variable} MATCHES "/MT")
                string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
              endif()
            endforeach()
          endif()
      endif()

      add_library(${PROJECT_NAME}_STATIC ${SOURCES_${PROJECT_NAME}} ${HEADERS_${PROJECT_NAME}})
      target_include_directories(${PROJECT_NAME}_STATIC PUBLIC ${PROJECT_SOURCE_DIR})
      target_include_directories(${PROJECT_NAME}_STATIC PUBLIC ${Boost_INCLUDE_DIRS})

      set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES CXX_STANDARD 17
                                            CXX_STANDARD_REQUIRED ON)
endif()
