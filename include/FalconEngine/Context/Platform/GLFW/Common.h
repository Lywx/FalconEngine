#pragma once

#include <FalconEngine/Context/Common.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
// NOTE(Wuxiang): Necessary for GLEW static library.
#if defined(FALCON_ENGINE_BUILD_STATIC)
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
