#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

#include <FalconEngine/Content/StbLibGuardBegin.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <FalconEngine/Content/StbLibGuardEnd.h>

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
    mAttachment(),
    mDimension(),
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
                    * size_t(mDimension[2]) * TexelSize[TextureFormatIndex(mFormat)];
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
ResourceCreationAccessMode
Texture::GetAccessMode() const
{
    return mAccessMode;
}

void
Texture::SetAccessModeInternal(ResourceCreationAccessMode accessMode)
{
    mAccessMode = accessMode;
}

ResourceCreationAccessUsage
Texture::GetAccessUsage() const
{
    return mAccessUsage;
}

void
Texture::SetAccessUsageInternal(ResourceCreationAccessUsage accessUsage)
{
    mAccessUsage = accessUsage;
}

bool
Texture::GetAttachmentEnabled(TextureMode textureMode) const
{
    return mAttachment[TextureModeIndex(textureMode)];
}

void
Texture::SetAttachmentEnabled(TextureMode textureMode)
{
    mAttachment[TextureModeIndex(textureMode)] = true;
}

void
Texture::ResetAttachmentEnabled(TextureMode textureMode)
{
    mAttachment.fill(false);

    SetAttachmentEnabled(textureMode);
}

unsigned char *
Texture::GetData()
{
    return mData;
}

const unsigned char *
Texture::GetData() const
{
    return mData;
}

size_t
Texture::GetDataSize() const
{
    return mDataSize;
}

std::array<int, 3>
Texture::GetDimension() const
{
    return mDimension;
}

int
Texture::GetDimension(int dimensionIndex) const
{
    return mDimension[dimensionIndex];
}

TextureFormat
Texture::GetFormat() const
{
    return mFormat;
}

int
Texture::GetMipmapLevel() const
{
    return mMipmapLevel;
}

ResourceStorageMode
Texture::GetStorageMode() const
{
    return mStorageMode;
}

TextureType Texture::GetTextureType() const
{
    return mType;
}

size_t
Texture::GetTexelSize() const
{
    return TexelSize[TextureFormatIndex(mFormat)];
}
}
