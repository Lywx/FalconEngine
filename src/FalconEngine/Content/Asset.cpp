#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Asset, Object);

Asset::Asset(const std::string& fileName, const std::string& filePath) :
    mFileName(fileName),
    mFilePath(filePath)
{
}

Asset::~Asset()
{
}

std::string
AddAssetExtension(const std::string& filePath)
{
    return filePath + u8".bin";
}

}
