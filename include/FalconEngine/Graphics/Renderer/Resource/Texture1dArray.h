#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN Texture1dArray :
public Texture1d
{
    FALCON_ENGINE_TEXTURE_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture1dArray(AssetSource assetSource,
                   const std::string & fileName,
                   const std::string & filePath,
                   int width,
                   int depth,
                   TextureFormat format,
                   ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
                   ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
                   int mipmapLevel = 0);
    virtual ~Texture1dArray();

public:
    virtual const Texture1d *
    GetTextureSlice(int index) const override final;

    void
    PushTextureSlice(const std::shared_ptr<Texture1d>& texture);

protected:
    // NOTE(Wuxiang): The Texture1D should not be released before owner of them
    // being released.
    std::vector<std::shared_ptr<Texture1d>> mTextureList;
};
FALCON_ENGINE_CLASS_END

}
