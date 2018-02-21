cmake_minimum_required(VERSION 3.1)

# NOTE(Wuxiang): Include guard.
if(FALCON_ENGINE_DEPENDENCY_INITIALIZED)
    return()
endif()

set(FALCON_ENGINE_DEPENDENCY_INITIALIZED TRUE)

# NOTE(Wuxiang): Necessary include.
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)

# Assimp
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    set(ASSIMP_LIBRARY_FILE assimp-vc140-mt)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(ASSIMP_LIBRARY_FILE assimp)
endif()

# Boost
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    set(BOOST_LIBRARY_FILE boost_filesystem boost_regex boost_system)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(BOOST_LIBRARY_FILE boost_filesystem boost_regex boost_system)
endif()

# D3D
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    set(D3D_LIBRARY_FILE D3D11)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    message(FATAL_ERROR "Direct3D API is not supported on Linux.")
endif()

# GL
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    set(GL_LIBRARY_FILE opengl32)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(GL_LIBRARY_FILE GL)
endif()
        
# GLEW
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    set(GLEW_LIBRARY_FILE glew32d)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(GLEW_LIBRARY_FILE GLEW)
endif()

# GLFW
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    fe_assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
    if(FALCON_ENGINE_BUILD_DYNAMIC)
        set(GLFW_LIBRARY_FILE glfw3dll)
    else()
        set(GLFW_LIBRARY_FILE glfw3)
    endif()
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(GLFW_LIBRARY_FILE glfw3)
endif()

# Qt
if(FALCON_ENGINE_PLATFORM_WINDOWS)
    fe_assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
    if(FALCON_ENGINE_BUILD_DYNAMIC)
        set(QT_LIBRARY_FILE Qt5Cored.dll Qt5Guid.dll Qt5OpenGLd.dll Qt5Widgetsd.dll)
    else()
        set(QT_LIBRARY_FILE Qt5Cored Qt5Guid Qt5OpenGLd Qt5Widgetsd)
    endif()
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    # TODO(Wuxiang): 2017-10-11 19:55 Add linux support.
    set(QT_LIBRARY_FILE)
endif()

if (FALCON_ENGINE_WINDOW_QT)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

