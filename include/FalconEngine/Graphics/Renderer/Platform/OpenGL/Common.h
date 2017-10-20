#pragma once

#include <FalconEngine/Graphics/Common.h>

// NOTE(Wuxiang): Choose between GL loader. GLEW or GLAD.
#if defined(FALCON_ENGINE_API_OPENGL_GLAD)
#include <FalconEngine/Context/Platform/GLAD/Common.h>
#elif defined(FALCON_ENGINE_API_OPENGL_GLEW)
#include <FalconEngine/Context/Platform/GLEW/Common.h>
#endif
