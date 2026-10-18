cmake_minimum_required(VERSION 4.3.1)

project(GMFN VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

if (NOT WIN32 OR NOT MSVC)
    message(FATAL_ERROR "${PROJECT_NAME} requires Windows and an MSVC-compatible compiler.")
endif ()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "${PROJECT_NAME} requires a 64-bit architecture.")
endif ()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

if (NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif ()

if (NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

if (NOT CMAKE_GENERATOR_IS_MULTI_CONFIG)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
        message(STATUS "CMAKE_BUILD_TYPE is not specified. Using default: ${CMAKE_BUILD_TYPE}")
    endif ()
endif ()

option(GMFN_STRICT  "Treat compiler warnings as errors" ON)
option(GMFN_BUILD   "Enable GMFN build" ON)
option(GMFN_INSTALL "Enable GMFN installation" ON)

if (GMFN_BUILD)
    add_subdirectory(GMFN)
endif ()

if (GMFN_INSTALL)
    install(DIRECTORY GMFN/include/
            TYPE INCLUDE
            COMPONENT devel)

    install(EXPORT GMFN
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
            NAMESPACE GMFN::
            COMPONENT devel
    )
endif ()