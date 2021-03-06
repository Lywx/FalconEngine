#pragma once

#include <FalconEngine/Core/Macro.h>

// NOTE(Wuxiang): Choose between GL loader. GLEW or GLAD.
#if defined(FALCON_ENGINE_API_OPENGL)
#if defined(FALCON_ENGINE_API_OPENGL_GLAD)
#include <FalconEngine/Platform/GLAD/GLADLib.h>
#elif defined(FALCON_ENGINE_API_OPENGL_GLEW)
#include <FalconEngine/Platform/GLEW/GLEWLib.h>
#endif
#endif