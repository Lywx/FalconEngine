#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/Renderer/Resource/TextureBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Texture2d : public TextureBuffer
{
public:
    FALCON_ENGINE_TEXTURE_DECLARE();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2d(AssetSource        assetSource,
              const std::string& fileName,
              const std::string& filePath,
              int                width,
              int                height,
              TextureFormat      format,
              BufferUsage        usage = BufferUsage::Static,
              int                mipmapLevel = 0);
    virtual ~Texture2d();

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int /* version */) const
    {
        ar << boost::serialization::base_object<const TextureBuffer>(*this);

        // NOTE(Wuxiang): mDataByteNum is serialized in TextureBuffer.
        for (int i = 0; i < mDataByteNum; ++i)
        {
            ar << mData[i];
        }
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int /* version */)
    {
        ar >> boost::serialization::base_object<TextureBuffer>(*this);

        // NOTE(Wuxiang): mDataByteNum is serialized in TextureBuffer.
        delete[] mData;
        mData = new unsigned char[mDataByteNum];
        for (int i = 0; i < mDataByteNum; ++i)
        {
            ar >> mData[i];
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

}


