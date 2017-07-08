#pragma once

#include <array>
#include <map>
#include <vector>

#include <cereal/access.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
// https://github.com/USCiLab/cereal/issues/286
#include <cereal/types/memory.hpp>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API TextureUnit
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

enum class FALCON_ENGINE_API TextureType
{
    None,

    Texture1d,
    Texture2d,
    Texture2dArray,
    Texture3d,
    TextureCube,

    Count
};

class Texture;

template <typename T>
TextureType
GetTextureType()
{
    // Don't get mixed up with RTTI classes which use RTTI klass::sType static member also.
    static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

    return T::sType;
}

enum class FALCON_ENGINE_API TextureFormat
{
    None,

    R8G8B8A8,

    Count
};

const size_t TexelSize[int(TextureFormat::Count)] =
{
    0, // None

    4, // R8G8B8A8
};

// @summary Thin layer describing what the most basic texture consists of. A texture
// doesn't necessarily have data storage because the a texture could simply made of
// array of existing textures.
class FALCON_ENGINE_API Texture : public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture();
    Texture(AssetSource        assetSource,
            const std::string& fileName,
            const std::string& filePath,
            int                width,
            int                height,
            int                depth,
            TextureFormat      format,
            TextureType        type,
            BufferStorageMode  storageMode,
            BufferUsage        usage,
            int                mipmapLevel);
    virtual ~Texture();

public:
    // Texture RGBA color channel number.
    int                mChannel = 0;

    // Texture dimension (width, height, depth).
    std::array<int, 3> mDimension;

    // Texture binary format, needed during construction.
    TextureFormat      mFormat;

    // Texture mipmap level, needed during construction.
    int                mMipmapLevel;

    // Texture type, needed during construction.
    TextureType        mType;

    // Texture buffer specific data.
    unsigned char     *mData;
    size_t             mDataSize;

    // Texture buffer storage mode, currently only in Host mode.
    BufferStorageMode  mStorageMode;

    // Texture buffer usage, needed during construction.
    BufferUsage        mUsage;

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive & ar)
    {
        ar & cereal::base_class<Asset>(this);

        ar & mChannel;
        ar & mDimension;
        ar & mFormat;
        ar & mMipmapLevel;
        ar & mType;

        // NOTE(Wuxiang): mData should be serialized in derived class.
        ar & mDataSize;

        ar & mStorageMode;
        ar & mUsage;
    }
};

}

#define FALCON_ENGINE_TEXTURE_DECLARE() \
public: \
    static const FalconEngine::TextureType sType;

#define FALCON_ENGINE_TEXTURE_IMPLEMENT(textureKlass, textureType) \
const FalconEngine::TextureType textureKlass::sType = textureType;

