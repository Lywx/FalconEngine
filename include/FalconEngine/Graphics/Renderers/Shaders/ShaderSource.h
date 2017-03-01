#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <unordered_map>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

class ShaderSource;
using ShaderSourceSharedPtr = std::shared_ptr<ShaderSource>;
using ShaderSourceUniquePtr = std::unique_ptr<ShaderSource>;

class ShaderSource : public Asset
{
public:
    ShaderSource(std::string fileName, std::string filePath);
    virtual ~ShaderSource();

public:
    std::string mSource;
};

}
