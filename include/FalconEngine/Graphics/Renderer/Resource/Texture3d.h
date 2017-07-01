#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/TextureStorage.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Texture3d : public TextureStorage
{
    FALCON_ENGINE_TEXTURE_DECLARE();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture3d(AssetSource assetSource, const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage =  BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture3d();
};

}
