#pragma once

#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class Renderer;
class Texture;

FALCON_ENGINE_CLASS_BEGIN PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture(Renderer * renderer, const Texture * texture);
    virtual ~PlatformTexture();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

    void *
    Map(BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap();

protected:
    GLuint         mBufferObj;

    GLuint         mTextureObj;
    GLuint         mTextureObjPrevious;
    const Texture *mTexturePtr;

    GLuint         mDimension[3];
    GLuint         mFormat;
    GLuint         mFormatInternal;
    GLuint         mType;
    GLuint         mUsage;
};
FALCON_ENGINE_CLASS_END

}


#endif
