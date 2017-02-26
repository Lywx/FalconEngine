#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/Renderers/Resources/TextureBuffer.h>

namespace FalconEngine
{

class Texture2d : public TextureBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2d(const std::string& fileName, const std::string& filePath, int width, int height, TextureFormat format, BufferUsage usage = BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture2d();

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << boost::serialization::base_object<const TextureBuffer>(*this);

        int width  = mDimension[0];
        int height = mDimension[1];
        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                ar << mData[w + h * width];
            }
        }
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> boost::serialization::base_object<TextureBuffer>(*this);

        int width  = mDimension[0];
        int height = mDimension[1];

        mData = new unsigned char[width * height];
        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                ar >> mData[w + h * width];
            }
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

typedef std::shared_ptr<Texture2d> Texture2dSharedPtr;
typedef std::unique_ptr<Texture2d> Texture2dUniquePtr;

}


