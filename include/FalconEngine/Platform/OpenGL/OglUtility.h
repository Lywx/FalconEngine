#pragma once

#include <FalconEngine/Platform/OpenGL/OglMapping.h>

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
