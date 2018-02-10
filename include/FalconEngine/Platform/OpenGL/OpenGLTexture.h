#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class Renderer;
class Texture;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture(Renderer *renderer, const Texture *texture);
    virtual ~PlatformTexture();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *,
           int textureUnit,
           const TextureShaderMaskList& textureShaderMaskList);

    void
    Disable(Renderer *,
            int textureUnit,
            const TextureShaderMaskList& textureShaderMaskList);

    void *
    Map(Renderer *,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode synchronization,
        int64_t offset,
        int64_t size);

    void
    Unmap(Renderer *);

private:
    void
    CreateBuffer();

    void
    CreateTexture();

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
#pragma warning(default: 4251)

}

#endif