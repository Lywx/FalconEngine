#include <FalconEngine/Graphics/Renderers/Texture2d.h>

#include <fstream>
#include <stdexcept>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/filesystem.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace boost;
using namespace std;

namespace FalconEngine
{

Texture2d::Texture2d()
{
}

Texture2d::~Texture2d()
{
    m_textureWidth = 0;
    m_textureHeight = 0;

    if (m_textureFileSource == TextureSource::Asset)
    {
        delete[] m_textureData;
    }
    else if (m_textureFileSource == TextureSource::File)
    {
        stbi_image_free(m_textureData);
    }
    else
    {
        // Ignore.
    }
}

void Texture2d::LoadFromAssetFile(std::string textureAssetFilePath)
{
    m_textureFilePath = textureAssetFilePath;
    m_textureFileSource = TextureSource::Asset;

    ifstream textureAssetStream(textureAssetFilePath);
    archive::binary_iarchive textureAssetArchive(textureAssetStream);
    textureAssetArchive >> *this;
    if (m_textureData == nullptr)
    {
        throw runtime_error("Failed to load texture asset.");
    }
}

void Texture2d::LoadFromTextureFile(std::string textureFilePath)
{
    m_textureFilePath = textureFilePath;
    m_textureFileSource = TextureSource::File;

    // NOTE(Wuxiang): Since the stb_image default loading format goes from top-left to bottom-right,
    // it is necessary to flip to make it compatible for OpenGL.
    stbi_set_flip_vertically_on_load(1);
    m_textureData = stbi_load(textureFilePath.c_str(),
                              &m_textureWidth,
                              &m_textureHeight,
                              &m_textureChannel,
                              STBI_rgb_alpha);
    if (m_textureData == nullptr)
    {
        throw runtime_error("Failed to load texture file.");
    }
}

//glGenTextures(1, )
//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, m_textureWidth, m_textureHeight, 1,
//                GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

}
