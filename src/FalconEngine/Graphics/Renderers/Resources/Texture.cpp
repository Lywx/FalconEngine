#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Texture, Asset);

Texture::Texture(std::string fileName, std::string filePath, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel) :
    Asset(fileName, filePath),
    mFormat(format),
    mData(nullptr),
    mDataByteNum(0),
    mMipmapLevel(mipmapLevel),
    mType(type),
    mUsage(usage)
{
}

Texture::~Texture()
{
    mDimension[0] = 0;
    mDimension[1] = 0;
    mDimension[2] = 0;

    delete[] mData;
}

}
