#pragma once

#include <string>

#include <boost/serialization/access.hpp>

#include <FalconEngine/Content/ContentInclude.h>

namespace FalconEngine
{

enum class AssetSource
{
    None,
    Normal,
    Stream,
};

class Asset : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    Asset(std::string fileName, std::string filePath);
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
        ar & mFileType;
    }
};

}
