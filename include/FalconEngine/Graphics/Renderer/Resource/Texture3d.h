#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Texture3d : public Texture
{
    FALCON_ENGINE_TEXTURE_DECLARE();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture3d(AssetSource assetSource,
              const std::string& fileName,
              const std::string& filePath,
              int width,
              int height,
              int depth,
              TextureFormat format,
              ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
              ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
              int mipmapLevel = 0);
    virtual ~Texture3d();
};

}
