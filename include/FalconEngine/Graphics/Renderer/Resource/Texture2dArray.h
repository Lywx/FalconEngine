#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/TextureArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

class Texture2d;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Texture2dArray : public TextureArray
{
    FALCON_ENGINE_TEXTURE_DECLARE();

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2dArray(AssetSource assetSource,
                   const std::string& fileName,
                   const std::string& filePath,
                   int width,
                   int height,
                   int depth,
                   TextureFormat format,
                   ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
                   ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
                   int mipmapLevel = 0);
    virtual ~Texture2dArray();

public:
    virtual const Texture2d *
    GetTextureSlice(int index) const override;

    void
    PushTextureSlice(std::shared_ptr<Texture2d> texture);

protected:
    // NOTE(Wuxiang): The Texture2D should not be released before owner of them
    // being released.
    std::vector<std::shared_ptr<Texture2d>> mTextureList;
};
#pragma warning(default: 4251)

}
