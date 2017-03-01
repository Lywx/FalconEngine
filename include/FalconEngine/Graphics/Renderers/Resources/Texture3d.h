#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/Renderers/Resources/TextureBuffer.h>

namespace FalconEngine
{

class Texture3d : public TextureBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture3d(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage =  BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture3d();
};

}
