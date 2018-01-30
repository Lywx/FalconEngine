#pragma once

#include <FalconEngine/Content/Common.h>

#include <list>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

class Asset;

class Font;

class Mesh;
class Model;
class ModelImportOption;

enum class FALCON_ENGINE_API CustomImporterPolicy
{
    Replacement,
    Supplement,
};

// @remark Derived class should add supported asset type into the supported list
// so that the asset importer will process the asset type using this custom importer.
FALCON_ENGINE_CLASS_BEGIN CustomImporter
{
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
protected:
    explicit CustomImporter(CustomImporterPolicy assetImportPolicy);

public:
    virtual ~CustomImporter();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
public:
    virtual bool
    Import(_IN_OUT_ Model                   * model,
           _IN_     const std::string &       modelFilePath,
           _IN_     const ModelImportOption & modelImportOption);

public:
    CustomImporterPolicy mAssetImportPolicy;
    std::list<AssetType> mAssetTypeList;
};
FALCON_ENGINE_CLASS_END

}
