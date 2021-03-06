#pragma once

#include <array>
#include <map>
#include <vector>

#include <FalconEngine/Content/CerealLibGuardBegin.h>
#include <cereal/access.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
// https://github.com/USCiLab/cereal/issues/286
#include <cereal/types/memory.hpp>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Resource.h>

namespace FalconEngine
{

enum class TextureMode
{
    Color,
    DepthStencil,
    Image,
    Texture,

    Count,
};

inline int
TextureModeIndex(TextureMode textureMode)
{
    return int(textureMode);
}

enum class TextureUnit
{
    Ambient   = 0,
    Diffuse   = 1,
    Emissive  = 2,
    Shininess = 3,
    Specular  = 4,

    Font      = 5,

    Count,
};

inline int
GetTextureUnit(TextureUnit textureUnit)
{
    return int(textureUnit);
}

enum class TextureType
{
    None,

    Texture1d,
    Texture1dArray,
    Texture2d,
    Texture2dArray,
    Texture3d,
    TextureCube,

    Count,
};

class Texture;

template <typename T>
TextureType
GetTextureType()
{
    static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

    return T::sTextureType;
}

enum class TextureFormat
{
    None,

    D16_UNORM,
    D24_UNORM_S8_UINT,
    R8G8B8A8_UINT,

    Count
};

inline int
TextureFormatIndex(TextureFormat format)
{
    return int(format);
}

const size_t TexelSize[int(TextureFormat::Count)] =
{
    0, // None

    2, // D16_UNORM
    4, // D24_UNORM_S8_UINT
    4, // R8G8B8A8_UINT
};

// @summary Thin layer describing what the most basic texture consists of. A texture
// doesn't necessarily have data storage because the a texture could simply made of
// array of existing textures.
FALCON_ENGINE_CLASS_BEGIN Texture :
public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture();
    Texture(AssetSource assetSource,
            const std::string & fileName,
            const std::string & filePath,
            int width,
            int height,
            int depth,
            TextureFormat format,
            TextureType type,
            ResourceCreationAccessMode accessMode,
            ResourceCreationAccessUsage accessUsage,
            ResourceStorageMode storageMode,
            int mipmapLevel);
    virtual ~Texture();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    ResourceCreationAccessMode
    GetAccessMode() const;

    void
    SetAccessModeInternal(ResourceCreationAccessMode accessMode);

    ResourceCreationAccessUsage
    GetAccessUsage() const;

    void
    SetAccessUsageInternal(ResourceCreationAccessUsage accessUsage);

    bool
    GetAttachmentEnabled(TextureMode textureMode) const;

    void
    SetAttachmentEnabled(TextureMode textureMode);

    void
    ResetAttachmentEnabled(TextureMode textureMode);

    unsigned char *
    GetData();

    const unsigned char *
    GetData() const;

    size_t
    GetDataSize() const;

    std::array<int, 3>
    GetDimension() const;

    int
    GetDimension(int dimensionIndex) const;

    TextureFormat
    GetFormat() const;

    int
    GetMipmapLevel() const;

    virtual const Texture *
    GetSlice(int textureIndex) const = 0;

    ResourceStorageMode
    GetStorageMode() const;

    TextureType
    GetTextureType() const;

    size_t
    GetTexelSize() const;

protected:
    // Texture runtime access usage, needed during construction.
    ResourceCreationAccessMode mAccessMode;
    ResourceCreationAccessUsage mAccessUsage;

    // Texture runtime attachment usage, need for Direct3D resource view pipeline
    // attachment.
    std::array<bool, int(TextureMode::Count)> mAttachment;

    // Texture RGBA color channel number.
    int mChannel = 0;

    // Texture dimension (width, height, depth).
    std::array<int, 3> mDimension;

    // Texture binary format, needed during construction.
    TextureFormat mFormat;

    // Texture mipmap level, needed during construction.
    int mMipmapLevel;

    // Texture buffer specific data.
    unsigned char *mData;
    size_t mDataSize;

    // Texture buffer storage mode, currently only in Host mode.
    ResourceStorageMode mStorageMode;

    // Texture type, needed during construction.
    TextureType mType;

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class cereal::access;
    template <class Archive>
    void save(Archive & ar) const
    {
        ar & cereal::base_class<Asset>(this);

        ar & mChannel;
        ar & mDimension;
        ar & mFormat;
        ar & mMipmapLevel;
        ar & mType;

        // NOTE(Wuxiang): mData should be serialized in derived class.
        ar & mDataSize;
    }

    template <class Archive>
    void load(Archive & ar)
    {
        ar & cereal::base_class<Asset>(this);

        ar & mChannel;
        ar & mDimension;
        ar & mFormat;
        ar & mMipmapLevel;
        ar & mType;

        // NOTE(Wuxiang): mData should be serialized in derived class.
        ar & mDataSize;

        // NOTE(Wuxiang): Those members are de-serialized with default value.
        mAccessMode = ResourceCreationAccessMode::GpuRead;
        mAccessUsage = ResourceCreationAccessUsage::Static;
        mStorageMode = ResourceStorageMode::Host;
    }
};
FALCON_ENGINE_CLASS_END

}

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(FalconEngine::Texture, cereal::specialization::member_load_save)

#define FALCON_ENGINE_TEXTURE_DECLARE \
public: \
    static const FalconEngine::TextureType sTextureType;

#define FALCON_ENGINE_TEXTURE_IMPLEMENT(textureKlass, textureType) \
const FalconEngine::TextureType textureKlass::sTextureType = textureType;


