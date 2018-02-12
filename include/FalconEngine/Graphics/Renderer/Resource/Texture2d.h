#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>

#include <cereal/cereal.hpp>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN Texture2d :
public Texture
{
    FALCON_ENGINE_TEXTURE_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2d();
    Texture2d(AssetSource assetSource,
              const std::string & fileName,
              const std::string & filePath,
              int width,
              int height,
              TextureFormat format,
              ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
              ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
              int mipmapLevel = 0);
    virtual ~Texture2d();

protected:
    Texture2d(AssetSource assetSource,
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

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual const Texture2d *
    GetTextureSlice(int textureIndex) const override;

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
FALCON_ENGINE_CLASS_END

}

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(FalconEngine::Texture2d, cereal::specialization::member_load_save)
