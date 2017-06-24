#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformTexture1d
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1d(const Texture1d *texture);
    ~PlatformTexture1d();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
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
    GLint  mDimension;

    GLuint mFormatInternal;
    GLuint mFormat;

    GLuint mType;
    GLuint mUsage;
};

}
