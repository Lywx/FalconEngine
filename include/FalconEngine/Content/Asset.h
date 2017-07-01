#pragma once

#include <FalconEngine/Content/Common.h>

#include <string>

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>

namespace FalconEngine
{

enum class FALCON_ENGINE_API AssetSource
{
    None,
    Normal,
    Stream,
    Virtual,
};

enum class AssetType
{
    None    = 0,

    Audio   = 1,
    Font    = 2,
    Model   = 3,
    Shader  = 4,
    Texture = 5,
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Asset
{
public:
    Asset();
    Asset(AssetSource assetSource, AssetType assetType, const std::string& fileName, const std::string& filePath);
    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;
    virtual ~Asset() noexcept;

public:
    AssetSource mAssetSource;

    AssetType   mAssetType;
    std::string mFileName;
    std::string mFilePath;

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive & ar)
    {
        // NOTE(Wuxiang): Don't need to serialize mAssetSource, because it is
        // changed when loading in different circumstances.
        ar & mAssetType;

        ar & mFileName;
        ar & mFilePath;
    }
};
#pragma warning(default: 4251)

FALCON_ENGINE_API std::string
AddAssetExtension(const std::string& filePath);

}