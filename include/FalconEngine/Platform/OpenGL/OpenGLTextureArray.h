#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <array>
#include <vector>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

class Renderer;
class TextureArray;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTextureArray
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTextureArray(Renderer *, const TextureArray *textureArray);
    virtual ~PlatformTextureArray();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(Renderer *, int textureUnit, const TextureShaderMaskList&);

    void
    Disable(Renderer *, int textureUnit, const TextureShaderMaskList&);

    void *
    Map(Renderer *,
        int textureIndex,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode synchronization,
        int64_t offset,
        int64_t size);

    void
    Unmap(Renderer *, int textureIndex);

protected:
    // The buffer object for each slice of texture
    std::vector<GLuint>             mBufferObjList;

    GLuint                          mTextureArrayObj;
    GLuint                          mTextureArrayObjPrevious;
    const TextureArray             *mTextureArrayPtr;

    // The dimension array for each slice of texture
    std::array<int, 3>              mDimension;
    GLuint                          mFormatInternal;
    GLuint                          mFormat;
    GLuint                          mType;
    GLuint                          mUsage;
};
#pragma warning(default: 4251)

}

#endif