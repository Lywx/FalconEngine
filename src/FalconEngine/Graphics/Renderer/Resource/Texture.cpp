#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

#include <FalconEngine/Core/Exception.h>
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
// NOTE(Wuxiang): This default constructor is used in deserialization for texture
// loading.
Texture::Texture() :
    mAccessMode(ResourceCreationAccessMode::None),
    mAccessUsage(ResourceCreationAccessUsage::None),
    mAttachment(),
    mDimension(),
    mFormat(TextureFormat::None),
    mMipmapLevel(0),
    mData(nullptr),
    mDataSize(0),
    mStorageMode(ResourceStorageMode::None),
    mType(TextureType::None)
{
}

Texture::Texture(AssetSource assetSource,
                 const std::string& fileName,
                 const std::string& filePath,
                 int width,
                 int height,
                 int depth,
                 TextureFormat format,
                 TextureType type,
                 ResourceCreationAccessMode accessMode,
                 ResourceCreationAccessUsage accessUsage,
                 ResourceStorageMode storageMode,
                 int mipmapLevel) :
    Asset(assetSource, AssetType::Texture, fileName, filePath),
    mAccessMode(accessMode),
    mAccessUsage(accessUsage),
    mFormat(format),
    mMipmapLevel(mipmapLevel),
    mStorageMode(storageMode),
    mType(type)
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
    if (mStorageMode == ResourceStorageMode::Device)
    {
        mDataSize = 0;
        mData = nullptr;
    }
    else if (mStorageMode == ResourceStorageMode::Host)
    {
        mDataSize = size_t(mDimension[0]) * size_t(mDimension[1])
                    * size_t(mDimension[2]) * TexelSize[int(mFormat)];
        mData = new unsigned char[mDataSize];
    }
    else
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

Texture::~Texture()
{
    FALCON_ENGINE_RENDERER_UNBIND(this);

    delete[] mData;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
TextureType Texture::GetTextureType() const
{
    return mType;
}
}
