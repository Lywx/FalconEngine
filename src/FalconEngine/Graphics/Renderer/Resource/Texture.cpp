#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture::Texture(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel) :
    Asset(fileName, filePath),
    mFormat(format),
    mMipmapLevel(mipmapLevel),
    mType(type),
    mUsage(usage)
{
    mDimension[0] = width;
    mDimension[1] = height;
    mDimension[2] = depth;
}

Texture::~Texture()
{
}

}
