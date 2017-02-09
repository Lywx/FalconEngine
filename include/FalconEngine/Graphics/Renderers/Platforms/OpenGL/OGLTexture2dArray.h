#pragma once

#include <vector>

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>

namespace FalconEngine
{

class PlatformTexture2dArray
{
public:
    PlatformTexture2dArray(const std::vector<Texture2d *> textures);
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
    GLuint                mTexture;
    GLuint                mTexturePrevious;
    std::vector<Vector2i> mDimension;       // The dimension array for each slice of texture
    GLuint                mFormatInternal;
    GLuint                mFormat;
    GLuint                mType;
    GLuint                mUsage;
};

}
