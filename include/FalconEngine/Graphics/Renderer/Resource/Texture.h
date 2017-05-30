#pragma once

#include <map>
#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Graphics/Header.h>
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
    static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

    return T::sTextureType;
}

enum class FALCON_ENGINE_API TextureFormat
{
    None,

    R8G8B8A8,

    Count
};

const int TexelSize[int(TextureFormat::Count)] =
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
    Texture(AssetSource        assetSource,
            const std::string& fileName,
            const std::string& filePath,
            int                width,
            int                height,
            int                depth,
            TextureFormat      format,
            TextureType        type,
            BufferUsage        usage,
            int                mipmapLevel);
    virtual ~Texture();

public:
    int            mChannel = 0;                                               // Texture RGBA color channel number.
    int            mDimension[3];                                              // Texture dimension (width, height, depth).

    // NOTE(Wuxiang): Initialization in constructor requires the following data members.

    TextureFormat  mFormat;                                                    // Texture binary format, needed during construction.
    int            mMipmapLevel;                                               // Texture mipmap level, needed during construction.
    TextureType    mType;                                                      // Texture type, needed during construction.
    BufferUsage    mUsage;                                                     // Texture buffer usage, needed during construction.

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int /* version */) const
    {
        ar << boost::serialization::base_object<const Asset>(*this);
        ar << mChannel;
        ar << mDimension;

        ar << mFormat;
        ar << mMipmapLevel;
        ar << mType;
        ar << mUsage;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int /* version */)
    {
        ar >> boost::serialization::base_object<Asset>(*this);
        ar >> mChannel;
        ar >> mDimension;

        ar >> mFormat;
        ar >> mMipmapLevel;
        ar >> mType;
        ar >> mUsage;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

}

#define FALCON_ENGINE_TEXTURE_DECLARE() \
public: \
    static const FalconEngine::TextureType sTextureType;

#define FALCON_ENGINE_TEXTURE_IMPLEMENT(textureKlass, textureType) \
const FalconEngine::TextureType textureKlass::sTextureType = textureType;

