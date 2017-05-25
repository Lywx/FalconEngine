#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <memory>
#include <boost/serialization/access.hpp>

#include <FalconEngine/Graphics/Renderer/Resource/TextureBuffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Texture3d : public TextureBuffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture3d(AssetSource assetSource, const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage =  BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture3d();
};

}
