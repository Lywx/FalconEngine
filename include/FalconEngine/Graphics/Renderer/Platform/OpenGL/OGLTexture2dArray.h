#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_ITEM_GRAPHICS PlatformTexture2dArray
{
public:
    PlatformTexture2dArray(const Texture2dArray *textures);
    ~PlatformTexture2dArray();

    void
    Enable(int textureUnit);

    void
    Disable(int textureUnit);

    void *
    Map(int arrayIndex, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(int arrayIndex, int mipmapLevel);

private:
    std::vector<GLuint>   mBuffer;          // The buffer object for each slice of texture

    std::vector<Vector2i> mDimension;       // The dimension array for each slice of texture
    GLuint                mFormatInternal;
    GLuint                mFormat;
    GLuint                mType;
    GLuint                mUsage;

    int                   mTextureArraySize;
    GLuint                mTexture;
    GLuint                mTexturePrevious;
};
#pragma warning(default: 4251)

}
