project(SFML-Sidescroller)
cmake_minimum_required(VERSION 2.8.8)

include(ExternalProject)
include(FindPkgConfig)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRCS ${SRC}/*.c*)
file(GLOB_RECURSE HDRS ${HDR}/*.h*)

SET(PIGA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/piga CACHE STRING "The directory of the piga repository.")

add_executable(Client ${SRCS} ${HDRS})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Client ${SFML_LIBRARIES})
endif()

find_package(Boost REQUIRED COMPONENTS system thread)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(Client ${Boost_LIBRARIES})
endif()

find_package(Box2D REQUIRED)
if(${BOX2D_FOUND})
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(Client ${BOX2D_LIBRARIES})
endif()

find_package(Lua 5.1 REQUIRED)
if(${LUA_FOUND})
    include_directories(${LUA_INCLUDE_DIR})
    target_link_libraries(Client lua5.1)

    message(STATUS "Lua: " ${LUA_LIBRARIES})
endif()

# Add piga
message(STATUS "Piga Dir: " ${PIGA_DIR})
add_subdirectory(${PIGA_DIR}/libpiga/ ${CMAKE_CURRENT_BINARY_DIR}/piga_dir/)
add_dependencies(Client piga)
include_directories(${LIBPIGA_INCLUDE_DIRECTORIES})
target_link_libraries(Client piga)

add_dependencies(Client piga)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
endif()
