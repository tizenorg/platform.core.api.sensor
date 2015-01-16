CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(capi-system-sensor)

# Setup for pkgconfig File
SET(fw_name "capi-system-sensor")
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(VERSION 1.0)

INCLUDE_DIRECTORIES(include)

# Build options
INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_name} REQUIRED dlog sensor capi-base-common)

FOREACH(flag ${${fw_name}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fPIC -Wall -Werror -g -fdump-rtl-expand")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS} -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl, --rpath=${LIB_INSTALL_DIR}")

# Internal Logging Option
#ADD_DEFINITIONS("-DTIZEN_DEBUG")

# Complile Source files
AUX_SOURCE_DIRECTORY(src SOURCES)
ADD_LIBRARY(${fw_name} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${fw_name} ${${fw_name}_LDFLAGS})
SET_TARGET_PROPERTIES(${fw_name} PROPERTIES VERSION ${FULLVER} SOVERSION ${MAJORVER} CLEAN_DIRECT_OUTPUT 1)
CONFIGURE_FILE(${fw_name}.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
INSTALL(TARGETS ${fw_name} DESTINATION ${LIB_INSTALL_DIR} COMPONENT RuntimeLibraries)
INSTALL(FILES include/sensors.h DESTINATION ${INCLUDE_INSTALL_DIR}/sensor)

# ###
IF(UNIX)
ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
ADD_CUSTOM_COMMAND(
        DEPENDS clean
        COMMENT "distribution clean"
        COMMAND find
        ARGS    .
        -not -name config.cmake -and \(
        -name tester.c -or
        -name Testing -or
        -name CMakeFiles -or
        -name cmake.depends -or
        -name cmake.check_depends -or
        -name CMakeCache.txt -or
        -name cmake.check_cache -or
        -name *.cmake -or
        -name Makefile -or
        -name core -or
        -name core.* -or
        -name gmon.out -or
        -name install_manifest.txt -or
        -name *.pc -or
        -name *~ \)
        | grep -v TC | xargs rm -rf
        TARGET  distclean
        VERBATIM
)
ENDIF(UNIX)

