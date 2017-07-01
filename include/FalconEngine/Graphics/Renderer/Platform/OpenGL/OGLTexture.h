#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLMapping.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture(GLuint textureTarget, const Texture *texture);
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
    Map(int arrayIndex, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(int arrayIndex, int mipmapLevel);

protected:
    GLuint         mBufferObj;

    GLuint         mTextureTarget;
    const Texture *mTexturePtr;
    GLuint         mTextureObj;
    GLuint         mTextureObjPrevious;

private:
    GLuint         mDimension[3];
    GLuint         mFormat;
    GLuint         mFormatInternal;
    GLuint         mType;
    GLuint         mUsage;
};
#pragma warning(default: 4251)

}
