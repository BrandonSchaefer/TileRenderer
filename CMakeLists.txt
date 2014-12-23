cmake_minimum_required (VERSION 3.0)
project (TILE_RENDERER)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++0x -pedantic -Wcast-align -Wempty-body -Wformat-security -Winit-self -Warray-bounds")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set (CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (RESDIR "${CMAKE_INSTALL_PREFIX}/share/sdl_backend/resources")
configure_file (${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)

file (GLOB _datafiles "${CMAKE_CURRENT_SOURCE_DIR}/resources/*")
install (FILES ${_datafiles} DESTINATION ${RESDIR})

add_subdirectory(src)

option(ENABLE_TESTS "Bulid tests" ON)

if (ENABLE_TESTS)
  add_subdirectory(tests)
endif ()
