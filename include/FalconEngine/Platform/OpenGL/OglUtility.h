#pragma once

#include <FalconEngine/Platform/OpenGL/Common.h>
#if defined(FALCON_ENGINE_API_OPENGL)

namespace FalconEngine
{

// @return previous bound texture
GLuint
BindTexture(TextureType textureType, GLuint texture);

// @return previous bound texture
GLuint
GetBoundTexture(TextureType textureType);

// @return previous bound sampler
GLuint
BindSampler(GLuint textureUnit, GLuint sampler);

}

#endif