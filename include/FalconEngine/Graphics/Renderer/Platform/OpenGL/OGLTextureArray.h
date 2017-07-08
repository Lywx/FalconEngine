#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>

namespace FalconEngine
{

class TextureArray;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTextureArray
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTextureArray(const TextureArray *textureArray);
    virtual ~PlatformTextureArray();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

    void *
    Map(int                       textureIndex,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(int textureIndex);

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
