#pragma once

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

namespace FalconEngine
{

class Texture1d : public Texture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture1d(std::string fileName, std::string filePath, TextureFormat format, BufferUsage usage = BufferUsage::Dynamic, int mipmapLevel = 0);
    virtual ~Texture1d();
};

typedef std::shared_ptr<Texture1d> Texture1dSharedPtr;

}
