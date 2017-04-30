cmake_minimum_required(VERSION 3.0)

# NOTE(Wuxiang): Necessary include.
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Utility.cmake)

# NOTE(Wuxiang): Modified from https://github.com/gongminmin/KlayGE/blob/develop/cmake/Platform.cmake
set(FALCON_ENGINE_PLATFORM_INITIALIZED TRUE)

# NOTE(Wuxiang): Necessary for generating Cmake compiler and system information.
enable_language(CXX)

#
# Architecture and platform
#

assert_defined(CMAKE_SYSTEM_NAME)

if(WIN32)
    set(FALCON_ENGINE_PLATFORM_NAME "win")
    set(FALCON_ENGINE_PLATFORM_WINDOWS TRUE)

    # Architecture on Visual Studio
    if(MSVC)
        assert_defined(CMAKE_GENERATOR)

        if(CMAKE_GENERATOR MATCHES "Win64")
            set(FALCON_ENGINE_ARCH_NAME "x64")
        else()
            set(FALCON_ENGINE_ARCH_NAME "x86")
        endif()
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(FALCON_ENGINE_PLATFORM_NAME "linux")
    set(FALCON_ENGINE_PLATFORM_LINUX TRUE)
endif()

# Architecture on non Visual Studio.
if(NOT DEFINED FALCON_ENGINE_ARCH_NAME)
    assert_defined(CMAKE_SYSTEM_PROCESSOR)

    if((CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64") OR (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64"))
        set(FALCON_ENGINE_ARCH_NAME "x64")
    else()
        set(FALCON_ENGINE_ARCH_NAME "x86")
    endif()
endif()

# Decide platform name based on architecture and OS
set(FALCON_ENGINE_PLATFORM_NAME ${FALCON_ENGINE_PLATFORM_NAME}_${FALCON_ENGINE_ARCH_NAME})

if (FALCON_ENGINE_PLATFORM_WINDOWS OR FALCON_ENGINE_PLATFORM_LINUX)
    set(FALCON_ENGINE_PLATFORM_DEVELOP TRUE)
else()
    set(FALCON_ENGINE_PLATFORM_DEVELOP FALSE)
endif()
