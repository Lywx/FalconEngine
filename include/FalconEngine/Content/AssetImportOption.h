#pragma once

#include <FalconEngine/Content/Header.h>

#include <FalconEngine/Content/ModelImportOption.h>
#include <FalconEngine/Content/TextureImportOption.h>

namespace FalconEngine
{

class FALCON_ENGINE_API AssetImportOption
{
public:
    static const ModelImportOption   mModelOption;
    static const TextureImportOption mTextureOption;
};

}
