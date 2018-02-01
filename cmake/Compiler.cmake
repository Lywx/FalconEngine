cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0054 NEW)

# NOTE(Wuxiang): Include guard.
if (FALCON_ENGINE_COMPILER_INITIALIZED)
    return()
endif()

set(FALCON_ENGINE_COMPILER_INITIALIZED TRUE)

# NOTE(Wuxiang): Necessary include.
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)

# NOTE(Wuxiang): Necessary for generating Cmake compiler and system information.
enable_language(CXX)

#
# Predefined macro
#

fe_assert_defined(FALCON_ENGINE_API_DIRECT3D)
if(FALCON_ENGINE_API_DIRECT3D)
    add_definitions(-DFALCON_ENGINE_API_DIRECT3D)
endif()

fe_assert_defined(FALCON_ENGINE_API_OPENGL)
if(FALCON_ENGINE_API_OPENGL)
    add_definitions(-DFALCON_ENGINE_API_OPENGL)
endif()

fe_assert_defined(FALCON_ENGINE_WINDOW_QT)
if(FALCON_ENGINE_WINDOW_QT)
    add_definitions(-DFALCON_ENGINE_WINDOW_QT)
endif()

fe_assert_defined(FALCON_ENGINE_WINDOW_GLFW)
if (FALCON_ENGINE_WINDOW_GLFW)
    add_definitions(-DFALCON_ENGINE_WINDOW_GLFW)
endif()

fe_assert_defined(FALCON_ENGINE_WINDOW_WIN32)
if (FALCON_ENGINE_WINDOW_WIN32)
    add_definitions(-DFALCON_ENGINE_WINDOW_WIN32)
endif()

fe_assert_defined(CMAKE_CXX_COMPILER_ID)

if(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_definitions(-DWIN32)
endif()

#
# Compiler, Linker Flags
#

fe_assert_defined(CMAKE_CXX_COMPILER_ID)

# Use Visual C++
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(FALCON_ENGINE_COMPILER_NAME "vc")
    set(FALCON_ENGINE_COMPILER_MSVC TRUE)

    if(MSVC_VERSION GREATER 1900)
        SET(FALCON_ENGINE_COMPILER_VERSION "141")
    else()
        SET(FALCON_ENGINE_COMPILER_VERSION "140")
    endif()

    #
    # Set compiler flags
    #

    # NOTE(Wuxiang): Short name for each flags:
    # /Gm (Enable Minimal Rebuild)
    # /MP (Build with Multiple Processes)
    # /EH (Exception Handling Model)
    # /Gw (Optimize Global Data)
    # /MT (Use Run-Time Library)
    # /MTd (Use LIBCMTD.lib)
    # /bigobj (Increase Number of Sections in .Obj file). This would freeze Visual Studio during build.
    set(CMAKE_CXX_FLAGS "/W4 /EHsc /std:c++14 /Zc:throwingNew /Zc:strictStrings /Zc:rvalueCast")

    if(MSVC_VERSION GREATER 1900)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
    endif()

    # /GL (Whole Program Optimization)
    # /Qpar (Auto-Parallelizer)
    # /fp (Specify Floating-Point Behavior)
    # /GS (Buffer Security Check)
    set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE	       "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS} /MD /fp:fast /MDd /Ob2 /GL /Qpar")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CMAKE_CXX_FLAGS} /MD /fp:fast /Ob2 /GL /Qpar")
    set(CMAKE_CXX_FLAGS_MINSIZEREL 	   "${CMAKE_CXX_FLAGS_MINSIZEREL} ${CMAKE_CXX_FLAGS} /MD /fp:fast /Ob1 /Qpar")

    fe_assert_defined(FALCON_ENGINE_ARCH_NAME)

    if(FALCON_ENGINE_ARCH_NAME MATCHES "x86")
        set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} /arch:SSE")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /arch:SSE")
        set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL} /arch:SSE")
    endif()

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GS-")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GS-")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /GS-")

    #
    # Set linker flags
    #

    # NOTE(Wuxiang): Prevent strangely setting the import library
    # /IMPLIB: https://msdn.microsoft.com/en-us/library/67wc07b9.aspx
    set(CMAKE_EXE_LINKER_FLAGS 	              "/pdbcompress /IMPLIB:")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG          "/DEBUG:FASTLINK")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG:FASTLINK /INCREMENTAL:NO /LTCG:incremental /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL     "/INCREMENTAL:NO /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE        "/INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF")

    set(CMAKE_SHARED_LINKER_FLAGS                "/pdbcompress")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG          "/DEBUG:FASTLINK")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG:FASTLINK /INCREMENTAL:NO /LTCG:incremental /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL     "/INCREMENTAL:NO /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE        "/INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF")

    set(CMAKE_MODULE_LINKER_FLAGS         "/pdbcompress")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG")

    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE        "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")
    set(CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO} /LTCG:incremental")

    fe_assert_defined(FALCON_ENGINE_ARCH_NAME)

    if(FALCON_ENGINE_ARCH_NAME MATCHES "x86")
        set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LARGEADDRESSAWARE")
    endif()

# Use GCC
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(FALCON_ENGINE_COMPILER_NAME "gcc")
    set(FALCON_ENGINE_COMPILER_GCC TRUE)

    #
    # Query compiler version
    #

    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
    list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
    list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
    set(FALCON_ENGINE_COMPILER_VERSION ${GCC_MAJOR}${GCC_MINOR})

    #
    # Set compiler Flags
    #

    # -Werror
    set(CMAKE_CXX_FLAGS "-W -Wall -Wno-attributes -Wno-unknown-pragmas")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS_DEBUG   	   "-DDEBUG -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE 	   "-DNDEBUG -O2")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -g -O2")
    set(CMAKE_CXX_FLAGS_MINSIZEREL 	   "-DNDEBUG -Os")

    if(FALCON_ENGINE_ARCH_NAME STREQUAL "x86")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    elseif((FALCON_ENGINE_ARCH_NAME STREQUAL "x64") OR (FALCON_ENGINE_ARCH_NAME STREQUAL "x86_64"))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    endif()

    #
    # Set linker flags
    #

    fe_assert_defined(FALCON_ENGINE_ARCH_NAME)

    if(FALCON_ENGINE_ARCH_NAME STREQUAL "x86")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m32")
        set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} -m32")

        if(FALCON_ENGINE_PLATFORM_WINDOWS)
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--large-address-aware")
            set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--large-address-aware")
            set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} -Wl,--large-address-aware")
        endif()
    elseif((FALCON_ENGINE_ARCH_NAME STREQUAL "x64") OR (FALCON_ENGINE_ARCH_NAME STREQUAL "x86_64"))
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m64")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m64")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m64")
    endif()

    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "-s")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "-s")
    set(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL "-s")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s")
endif()

# Set platform specific flags
if(FALCON_ENGINE_PLATFORM_LINUX)

    # NOTE(Wuxiang): Necessary for shared library
    # https://en.wikipedia.org/wiki/Position-independent_code
    set(CMAKE_CXX_FLAGS "-fpic ${CMAKE_CXX_FLAGS}")
endif()

# Decide output suffix based on compiler and its version
fe_assert_defined(FALCON_ENGINE_COMPILER_NAME)
fe_assert_defined(FALCON_ENGINE_COMPILER_VERSION)

set(FALCON_ENGINE_OUTPUT_SUFFIX -${FALCON_ENGINE_COMPILER_NAME}${FALCON_ENGINE_COMPILER_VERSION})
