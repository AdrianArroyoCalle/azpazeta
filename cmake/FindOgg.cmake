# Copied from http://code.google.com/p/osgaudio/source/browse/trunk/CMakeModules/FindOGG.cmake
# Locate OGG
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $OGGDIR is an environment variable that would
# correspond to the ./configure --prefix=$OGGDIR
# used in building OGG.

SET(OGG_SEARCH_PATHS
        ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/lib
        ${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies/lib
        ${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies/lib
)

SET(MSVC_YEAR_NAME)
IF (MSVC_VERSION GREATER 1599)                # >= 1600
        SET(MSVC_YEAR_NAME VS2010)
ELSEIF(MSVC_VERSION GREATER 1499)        # >= 1500
        SET(MSVC_YEAR_NAME VS2008)
ELSEIF(MSVC_VERSION GREATER 1399)        # >= 1400
        SET(MSVC_YEAR_NAME VS2005)
ELSEIF(MSVC_VERSION GREATER 1299)        # >= 1300
        SET(MSVC_YEAR_NAME VS2003)
ELSEIF(MSVC_VERSION GREATER 1199)        # >= 1200
        SET(MSVC_YEAR_NAME VS6)
ENDIF()

FIND_PATH(OGG_INCLUDE_DIR
        NAMES ogg/ogg.h ogg/os_types.h
        HINTS
        $ENV{OGGDIR}
        $ENV{OGG_PATH}
        PATH_SUFFIXES include
        PATHS ${OGG_SEARCH_PATHS}
)

FIND_LIBRARY(OGG_LIBRARY
        NAMES ogg libogg liblibogg
        HINTS
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        CMAKE_FIND_FRAMEWORK NEVER
        $ENV{OGGDIR}
        $ENV{OGG_PATH}
        PATH_SUFFIXES lib lib64 win32/Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
        PATHS ${OGG_SEARCH_PATHS}
)

# First search for d-suffixed libs
FIND_LIBRARY(OGG_LIBRARY_DEBUG
        NAMES oggd ogg_d liboggd libogg_d liblibogg_d
        HINTS
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_PATH
        CMAKE_FIND_FRAMEWORK NEVER
        $ENV{OGGDIR}
        $ENV{OGG_PATH}
        PATH_SUFFIXES lib lib64 win32/Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
        PATHS ${OGG_SEARCH_PATHS}
)

IF(NOT OGG_LIBRARY_DEBUG)
        # Then search for non suffixed libs if necessary, but only in debug dirs
        FIND_LIBRARY(OGG_LIBRARY_DEBUG
                NAMES ogg libogg liblibogg
                HINTS
                NO_DEFAULT_PATH
                NO_CMAKE_ENVIRONMENT_PATH
                NO_CMAKE_SYSTEM_PATH
                NO_SYSTEM_ENVIRONMENT_PATH
                NO_CMAKE_PATH
                CMAKE_FIND_FRAMEWORK NEVER
                $ENV{OGGDIR}
                $ENV{OGG_PATH}
                PATH_SUFFIXES win32/Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
                PATHS ${OGG_SEARCH_PATHS}
        )
ENDIF()


IF(OGG_LIBRARY)
        IF(OGG_LIBRARY_DEBUG)
                SET(OGG_LIBRARIES optimized "${OGG_LIBRARY}" debug "${OGG_LIBRARY_DEBUG}")
        ELSE()
                SET(OGG_LIBRARIES "${OGG_LIBRARY}")                # Could add "general" keyword, but it is optional
        ENDIF()
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGG DEFAULT_MSG OGG_LIBRARIES OGG_INCLUDE_DIR)