#pragma once

#include <FalconEngine/Content/Header.h>

#include <string>

#include <boost/serialization/access.hpp>

namespace FalconEngine
{

enum class FALCON_ENGINE_ITEM_CORE AssetSource
{
    None,
    Normal,
    Stream,
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_ITEM_CORE Asset
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
    void serialize(Archive & ar, const unsigned int /* version */)
    {
        ar & mFileName;
        ar & mFilePath;

        // NOTE(Wuxiang): Don't need to serialize mFileType, because it is
        // changed when loading in different circumstances.
    }
};
#pragma warning(default: 4251)

FALCON_ENGINE_ITEM_CORE std::string
AddAssetExtension(const std::string& filePath);

}
