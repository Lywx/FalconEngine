#pragma once

#include <FalconEngine/Context/Common.h>

// NOTE(Wuxiang): Use GLEW static library.
#if defined(FALCON_ENGINE_BUILD_STATIC)
#define GLEW_STATIC
#endif
#include <GL/glew.h>