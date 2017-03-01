#pragma once

#include <FalconEngine/Graphics/Renderer/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderer/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture2d.h>

namespace FalconEngine
{

class PlatformTexture2d
{
public:
    PlatformTexture2d(const Texture2d *texture);
    ~PlatformTexture2d();

    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

    void *
    Map(int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(int mipmapLevel);

private:
    GLuint mBuffer;

    GLuint mTexture;
    GLuint mTexturePrevious;
    GLint  mDimension[3];

    GLuint mFormatInternal;
    GLuint mFormat;

    GLuint mType;
    GLuint mUsage;
};

}
