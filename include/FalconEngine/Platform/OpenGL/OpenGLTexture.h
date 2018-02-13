#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

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
    Enable(Renderer *,
           int textureUnit,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(Renderer *,
            int textureUnit,
            const TextureShaderMaskList & textureShaderMaskList);

    void *
    Map(Renderer *,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void *
    Map(Renderer *,
        int textureIndex,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(Renderer * renderer);

    void
    Unmap(Renderer * renderer, int textureIndex);

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    AllocateBuffer();

    virtual void
    AllocateTexture() = 0;

    void
    CreateBuffer();

    void
    CreateTexture();

    void
    FillBuffer();

protected:
    std::vector<GLuint> mBufferObjList;

    GLuint mTextureObj;
    GLuint mTextureObjPrevious;
    const Texture *mTexturePtr;

    std::array<int, 3> mDimension;
    int mMipmapLevel;

    GLuint mFormat;
    GLuint mFormatInternal;
    GLuint mType;
    GLuint mUsage;
};
FALCON_ENGINE_CLASS_END

}

#endif