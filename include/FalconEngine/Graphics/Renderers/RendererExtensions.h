#pragma once

#define FALCON_ENGINE_USE_OPENGL 1
#include <FalconEngine/GraphicsInclude.h>

#if FALCON_ENGINE_USE_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#endif