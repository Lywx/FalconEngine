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
    assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
    if(FALCON_ENGINE_BUILD_DYNAMIC)
        set(GLFW_LIBRARY_FILE glfw3dll)
    else()
        set(GLFW_LIBRARY_FILE glfw3)
    endif()
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(GLFW_LIBRARY_FILE glfw3)
endif()
