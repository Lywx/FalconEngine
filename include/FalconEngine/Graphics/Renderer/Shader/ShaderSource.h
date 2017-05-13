#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <unordered_map>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

class ShaderSource;
using ShaderSourceSharedPtr = std::shared_ptr<ShaderSource>;
using ShaderSourceUniquePtr = std::unique_ptr<ShaderSource>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API ShaderSource : public Asset
{
public:
    ShaderSource(std::string fileName, std::string filePath);
    virtual ~ShaderSource();

public:
    std::string mSource;
};
#pragma warning(default: 4251)

}
