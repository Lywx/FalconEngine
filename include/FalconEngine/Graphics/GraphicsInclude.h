#pragma once

#include <FalconEngine/Core.h>
#include <FalconEngine/Math.h>

#define FALCON_ENGINE_API_OPENGL 1
#if FALCON_ENGINE_API_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

