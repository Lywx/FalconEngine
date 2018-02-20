#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

class ShaderSource;

FALCON_ENGINE_CLASS_BEGIN ShaderSource :
public Asset
{
public:
    ShaderSource(AssetSource assetSource, std::string fileName, std::string filePath);
    virtual ~ShaderSource();

public:
    std::string mSource;
};
FALCON_ENGINE_CLASS_END

}
