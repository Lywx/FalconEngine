#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>

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
