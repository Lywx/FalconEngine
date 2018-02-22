#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN Texture2dArray :
public Texture2d
{
    FALCON_ENGINE_TEXTURE_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2dArray(int width,
                   int height,
                   int depth,
                   TextureFormat format,
                   ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
                   ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
                   ResourceStorageMode storageMode = ResourceStorageMode::Host,
                   int mipmapLevel = 0);

    Texture2dArray(AssetSource assetSource,
                   const std::string & fileName,
                   const std::string & filePath,
                   int width,
                   int height,
                   int depth,
                   TextureFormat format,
                   ResourceCreationAccessMode accessMode = ResourceCreationAccessMode::GpuRead,
                   ResourceCreationAccessUsage accessUsage = ResourceCreationAccessUsage::Static,
                   ResourceStorageMode storageMode = ResourceStorageMode::Host,
                   int mipmapLevel = 0);

    virtual ~Texture2dArray();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual const Texture2d *
    GetSlice(int index) const override final;

    void
    PushSlice(const std::shared_ptr<Texture2d>& texture);

protected:
    // NOTE(Wuxiang): The Texture2D should not be released before owner of them
    // being released.
    std::vector<std::shared_ptr<Texture2d>> mTextureList;
};
FALCON_ENGINE_CLASS_END

}
