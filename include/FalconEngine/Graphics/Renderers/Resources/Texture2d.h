#pragma once

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

namespace FalconEngine
{

class Texture2d : public Texture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2d(std::string fileName, std::string filePath, TextureFormat format, BufferUsage usage = BufferUsage::Dynamic, int mipmapLevel = 0);
    virtual ~Texture2d();

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << boost::serialization::base_object<const Texture>(*this);

        int width  = mDimension[0];
        int height = mDimension[1];
        for (int w = 0; w < width; ++w)
        {
            for (int h = 0; h < height; ++h)
            {
                ar << mData[w + h * width];
            }
        }
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> boost::serialization::base_object<Texture>(*this);

        int width  = mDimension[0];
        int height = mDimension[1];

        mData = new unsigned char[width * height];
        for (int w = 0; w < width; ++w)
        {
            for (int h = 0; h < height; ++h)
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


