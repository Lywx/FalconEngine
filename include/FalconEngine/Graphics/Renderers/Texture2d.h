#pragma once

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Texture.h>

namespace FalconEngine
{

class Texture2d : public Texture
{
private:
    enum class TextureSource
    {
        None,
        Asset,
        File,
    };

public:
    Texture2d();
    ~Texture2d();

    // TODO
    void
    LoadFromAssetFile(std::string textureAssetFilePath);

    void
    LoadFromTextureFile(std::string textureFilePath);

    std::string    m_textureFilePath;
    TextureSource  m_textureFileSource = TextureSource::None;

    int            m_textureWidth = 0;
    int            m_textureHeight = 0;
    int            m_textureChannel = 0;
    unsigned char *m_textureData = nullptr;

    /************************************************************************/
    /* Asset Serialization                                                  */
    /************************************************************************/
    friend class boost::serialization::access;
    template <typename TArchive>
    void serialize(TArchive & ar, const unsigned int version)
    {
        delete[] m_textureData;

        ar & m_textureWidth;
        ar & m_textureHeight;

        m_textureData = new unsigned char[m_textureWidth * m_textureHeight];

        for (int w = 0; w < m_textureWidth; ++w)
        {
            for (int h = 0; h < m_textureHeight; ++h)
            {
                ar & m_textureData[w + h * m_textureWidth];
            }
        }
    }
};

typedef std::shared_ptr<Texture2d> Texture2dPtr;

}
