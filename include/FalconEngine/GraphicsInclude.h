#pragma once

#include <FalconEngine/CoreInclude.h>
#include <FalconEngine/Math.h>

#define FALCON_ENGINE_USE_OPENGL 1
#if FALCON_ENGINE_USE_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#endif

