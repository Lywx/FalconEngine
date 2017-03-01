#pragma once

#include <string>

#include <boost/serialization/access.hpp>

#include <FalconEngine/ContentInclude.h>

namespace FalconEngine
{

enum class AssetSource
{
    None,
    Normal,
    Stream,
};

class Asset
{
public:
    Asset(const std::string& fileName, const std::string& filePath);
    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;
    virtual ~Asset() noexcept;

public:
    std::string mFileName;
    std::string mFilePath;
    AssetSource mFileType = AssetSource::None;

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & mFileName;
        ar & mFilePath;

        // NOTE(Wuxiang): Don't need to serialize mFileType, because it is
        // changed when loading in different circumstances.
    }
};

std::string
AddAssetExtension(const std::string& filePath);

}
