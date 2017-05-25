#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <unordered_map>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

class ShaderSource;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API ShaderSource : public Asset
{
public:
    ShaderSource(AssetSource assetSource, std::string fileName, std::string filePath);
    virtual ~ShaderSource();

public:
    std::string mSource;
};
#pragma warning(default: 4251)

}
