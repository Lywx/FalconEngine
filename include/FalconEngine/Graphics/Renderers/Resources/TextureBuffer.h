#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

namespace FalconEngine
{

class TextureBuffer : public Texture
{
    FALCON_ENGINE_RTTI_DECLARE;

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
    void save(Archive & ar, const unsigned int version) const
    {
        ar << boost::serialization::base_object<const Texture>(*this);
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> boost::serialization::base_object<Texture>(*this);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

}
