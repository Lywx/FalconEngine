#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

#pragma warning(disable : 4244)
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#pragma warning(default : 4244)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture::Texture() :
    mDimension(),
    mFormat(TextureFormat::None),
    mMipmapLevel(0),
    mType(TextureType::None),
    mData(nullptr),
    mDataSize(0),
    mStorageMode(BufferStorageMode::Host),
    mUsage(BufferUsage::None)
{
}

Texture::Texture(AssetSource        assetSource,
                 const std::string& fileName,
                 const std::string& filePath,
                 int                width,
                 int                height,
                 int                depth,
                 TextureFormat      format,
                 TextureType        type,
                 BufferStorageMode  storageMode,
                 BufferUsage        usage,
                 int                mipmapLevel) :
    Asset(assetSource, AssetType::Texture, fileName, filePath),
    mFormat(format),
    mMipmapLevel(mipmapLevel),
    mType(type),
    mStorageMode(storageMode),
    mUsage(usage)
{
    // Test validity of dimension.
    if (width < 1 || height < 1 || depth < 1)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Invalid texture dimension.");
    }

    mDimension[0] = width;
    mDimension[1] = height;
    mDimension[2] = depth;

    // Allocate texture storage.
    if (mStorageMode == BufferStorageMode::Host)
    {
        mDataSize = size_t(mDimension[0]) * size_t(mDimension[1]) * size_t(mDimension[2]) * TexelSize[int(mFormat)];
        mData = new unsigned char[mDataSize];
    }
    else
    {
        mData = nullptr;
        mDataSize = 0;
    }
}

Texture::~Texture()
{
    FALCON_ENGINE_RENDERER_UNBIND(this);

    delete[] mData;
}

}
