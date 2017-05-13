#pragma once

#include <FalconEngine/Graphics/Header.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

class FALCON_ENGINE_API TextureBuffer : public Texture
{
public:
    TextureBuffer(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel);
    virtual ~TextureBuffer();

public:
    unsigned char *mData;
    int            mDataByteNum;

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int /* version */) const
    {
        ar << boost::serialization::base_object<const Texture>(*this);
        ar << mDataByteNum;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int /* version */)
    {
        ar >> boost::serialization::base_object<Texture>(*this);
        ar >> mDataByteNum;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

}
