#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformTexture2d : public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2d(const Texture2d *texture);
    ~PlatformTexture2d();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void *
    Map(int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(int mipmapLevel);

private:
    GLuint mBufferObj;
    GLuint mTextureObj;
    GLuint mTextureObjPrevious;

    GLint  mDimension[2];
    GLuint mFormatInternal;
    GLuint mFormat;
    GLuint mType;
    GLuint mUsage;
};

}
