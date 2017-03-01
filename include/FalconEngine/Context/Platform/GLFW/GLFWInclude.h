#pragma once

#include <FalconEngine/ContextInclude.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif