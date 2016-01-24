project(SFML-Sidescroller)
cmake_minimum_required(VERSION 2.8.8)

include(ExternalProject)
include(FindPkgConfig)

set(SFML_SIDESCROLLER_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(SFML_SIDESCROLLER_VERSION_MINOR "9" CACHE STRING "Minor-Version")
set(SFML_SIDESCROLLER_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(SFML_SIDESCROLLER_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(SFML_SIDESCROLLER_VERSION ${SFML_SIDESCROLLER_VERSION_MAJOR}.${SFML_SIDESCROLLER_VERSION_MINOR}.${SFML_SIDESCROLLER_VERSION_PATCH}.${SFML_SIDESCROLLER_VERSION_TWEAK})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRCS ${SRC}/*.c*)
file(GLOB_RECURSE HDRS ${HDR}/*.h*)

SET(PIGA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/piga CACHE STRING "The directory of the piga repository.")

add_executable(SFMLSidescrollerClient ${SRCS} ${HDRS})

find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(${SFML_FOUND})
    message(STATUS ${SFML_LIBRARIES})
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFMLSidescrollerClient ${SFML_LIBRARIES})
endif()

find_package(Boost REQUIRED COMPONENTS system thread)

if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(SFMLSidescrollerClient ${Boost_LIBRARIES})
endif()

find_package(Box2D REQUIRED)
if(${BOX2D_FOUND})
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(SFMLSidescrollerClient ${BOX2D_LIBRARIES})
endif()

find_package(Lua 5.1 REQUIRED)
if(${LUA_FOUND})
    include_directories(${LUA_INCLUDE_DIR})
    target_link_libraries(SFMLSidescrollerClient lua5.1)

    message(STATUS "Lua: " ${LUA_LIBRARIES})
endif()

find_package(Libpiga REQUIRED)
if(${Libpiga_FOUND})
    target_link_libraries(SFMLSidescrollerClient ${Libpiga_LIBRARIES})
    include_directories(${Libpiga_INCLUDE_DIRS})
endif()

set_property(TARGET SFMLSidescrollerClient PROPERTY VERSION ${SFML_SIDESCROLLER_VERSION})

install(TARGETS SFMLSidescrollerClient EXPORT SFMLSidescrollerClientTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    RUNTIME DESTINATION bin)

# Data files
install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
    DESTINATION ../var/sfml-sidescroller)

# Game package
install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/config.yml
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/icon.png
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/chooser-background.png
    DESTINATION ../var/piga/Games/SFML-Sidescroller/)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An original sidescrolling SHMUP.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${SFML_SIDESCROLLER_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SFML_SIDESCROLLER_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SFML_SIDESCROLLER_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${SFML_SIDESCROLLER_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_NAME "sfml-sidescroller")
set(CPACK_DEBIAN_PACKAGE_HOMEPAHE "https://github.com/maximaximal/sfml-sidescroller-revived")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
"libstdc++6 (>= 4.9.2-10), piga-libpiga (>= 0.6.0), libsfml-audio2 (>= 2.1), libsfml-graphics2 (>= 2.1), libsfml-network2 (>= 2.1), libsfml-system2 (>= 2.1), libsfml-window2 (>= 2.1), libboost-thread1.55.0 (>= 1.55.0), libboost-system1.55.0 (>= 1.55.0), libbox2d2.3.0 (>= 2.3.1), liblua5.1-0 (>= 5.1.5)")
set(CPACK_PACKAGE_NAME "sfml-sidescroller")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)

# Activate C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ${CMAKE_CXX_FLAGS} "-Wall -std=c++11 -lrt ${CMAKE_CXX_FLAGS}")
endif()
