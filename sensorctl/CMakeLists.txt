cmake_minimum_required(VERSION 2.6)
project(sensorctl CXX)
include(GNUInstallDirs)

# Setup For pkgconfig File
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "${PREFIX}/bin")
SET(LIBDIR "${PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(INCLUDEDIR "${PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
SET(VERSION 1.0)

INCLUDE(FindPkgConfig)
pkg_check_modules(pkgs REQUIRED glib-2.0)

add_definitions(${rpkgs_CFLAGS})
add_definitions(-DPREFIX="${CMAKE_INSTALL_PREFIX}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FOREACH(flag ${pkgs_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

# Common Options
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -omit-frame-pointer -std=gnu++0x")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdata-sections -ffunction-sections")

add_definitions(-DUSE_DLOG_LOG)

# Installing files
add_executable(sensorctl src/sensorctl.cpp)
SET_TARGET_PROPERTIES(sensorctl PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(sensorctl glib-2.0 dlog capi-system-sensor)
INSTALL(TARGETS sensorctl DESTINATION /usr/bin/)

