CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(capi-system-sensor)
INCLUDE(GNUInstallDirs)

SET(DEPENDENTS "dlog sensor capi-base-common")

IF("${PROFILE}" STREQUAL "mobile" OR "${PROFILE}" STREQUAL "wearable")
	SET(DEPENDENTS "${DEPENDENTS} context-common")
ENDIF()

SET(VERSION ${FULLVER})
SET(PREFIX ${CMAKE_INSTALL_PREFIX})

SET(PC_NAME ${PROJECT_NAME})
SET(PC_DESCRIPTION "Sensor C-API library")
SET(PC_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/sensor")
SET(PC_DEPENDENTS "${DEPENDENTS}")
SET(PC_LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(PC_LDFLAGS "-l${PROJECT_NAME}")

INCLUDE_DIRECTORIES(include ${CMAKE_CURRENT_SOURCE_DIR})

# Build options
INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(${PROJECT_NAME} REQUIRED ${DEPENDENTS})

FOREACH(flag ${${PROJECT_NAME}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fPIC -Wall -Werror -g -fdump-rtl-expand")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS} -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl, --rpath=${LIB_INSTALL_DIR}")

# Internal Logging Option
#ADD_DEFINITIONS("-DTIZEN_DEBUG")

# Compile Source files
SET(SOURCES src/geomagnetic_field.c
            src/fusion_util.c
            src/sensor.cpp)

IF("${PROFILE}" STREQUAL "mobile" OR "${PROFILE}" STREQUAL "wearable")
	SET(SOURCES ${SOURCES} src/sensor_recorder.cpp)
ELSE()
	SET(SOURCES ${SOURCES} src/sensor_recorder_dummy.cpp)
ENDIF()

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${${PROJECT_NAME}_LDFLAGS})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION ${FULLVER} SOVERSION ${MAJORVER} CLEAN_DIRECT_OUTPUT 1)
CONFIGURE_FILE(${PROJECT_NAME}.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries)
INSTALL(FILES include/sensor.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sensor)

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

