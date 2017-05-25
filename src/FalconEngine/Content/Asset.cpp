#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Asset::Asset(AssetSource assetSource, AssetType assetType, const std::string& fileName, const std::string& filePath) :
    mAssetSource(assetSource),
    mAssetType(assetType),
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
