#pragma once

// API
// SWITCH(Wuxiang): Uncommon this to choose API flag.
// #define FALCON_ENGINE_API_DIRECT3D
// #define FALCON_ENGINE_API_OPENGL
// #define FALCON_ENGINE_API_OPENGL_GLAD
// #define FALCON_ENGINE_API_OPENGL_GLEW

// Compiler
// SWITCH(Wuxiang): Uncommon this to choose compiler flag.
// #define FALCON_ENGINE_COMPILER_MSVC
// #define FALCON_ENGINE_COMPILER_GCC

// OS
// SWITCH(Wuxiang): Uncommon this to choose OS flag.
// #define FALCON_ENGINE_OS_WINDOWS
// #define FALCON_ENGINE_OS_LINUX

// DLL
#define FALCON_ENGINE_API

#if defined(_DEBUG)
#define FALCON_ENGINE_DEBUG
#endif

#if defined(FALCON_ENGINE_DEBUG)
#define FALCON_ENGINE_DEBUG_GRAPHICS
#define FALCON_ENGINE_DEBUG_MEMORY
#endif