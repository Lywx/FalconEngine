#pragma once

#include <memory>

#include <cereal/access.hpp>

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Texture1d : public Texture
{
    FALCON_ENGINE_TEXTURE_DECLARE();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture1d();
    Texture1d(AssetSource        assetSource,
              const std::string& fileName,
              const std::string& filePath,
              int                width,
              TextureFormat      format,
              BufferUsage        usage = BufferUsage::Static,
              int                mipmapLevel = 0);
    virtual ~Texture1d();

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class cereal::access;
    template<class Archive>
    void save(Archive & ar) const
    {
        ar & cereal::base_class<Texture>(this);

        ar & cereal::binary_data(mData, mDataSize);
    }

    template<class Archive>
    void load(Archive & ar)
    {
        delete[] mData;

        ar & cereal::base_class<Texture>(this);

        // NOTE(Wuxiang): mDataByteNum is serialized in TextureBuffer. It may
        // be changed by serialization result so that it needs a new memory
        // location.
        mData = new unsigned char[mDataSize];

        ar & cereal::binary_data(mData, mDataSize);
    }
};

}

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(FalconEngine::Texture1d, cereal::specialization::member_load_save)
