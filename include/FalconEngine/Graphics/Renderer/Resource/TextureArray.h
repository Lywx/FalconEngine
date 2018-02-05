#pragma once

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API TextureArray : public Texture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    TextureArray(AssetSource assetSource,
                 const std::string& fileName,
                 const std::string& filePath,
                 int width,
                 int height,
                 int depth,
                 TextureFormat format,
                 TextureType type,
                 ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
                 ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
                 int mipmapLevel = 0);
    virtual ~TextureArray();

public:
    virtual const Texture *
    GetTextureSlice(int textureIndex) const = 0;
};
#pragma warning(default: 4251)

}
