#pragma once

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture.h>

namespace FalconEngine
{

class Texture1d : public Texture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture1d(const std::string& fileName, const std::string& filePath, TextureFormat format, BufferUsage usage = BufferUsage::Dynamic, int mipmapLevel = 0);
    virtual ~Texture1d();
};

}
