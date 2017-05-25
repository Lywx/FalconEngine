#pragma once

#include <FalconEngine/Content/Header.h>

#include <list>
#include <unordered_map>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Content/CustomImporter.h>

namespace FalconEngine
{

class Asset;
class AssetManager;

class Mesh;
class Model;

class CustomImporter;

// TODO(Wuxiang): Support multi-threading asset importing.
// @remark Represents a thread-safe asset importer.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API AssetImporter final
{
    friend class AssetManager;

public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static AssetImporter *
    GetInstance()
    {
        static AssetImporter sAssetImporter;
        return &sAssetImporter;
    }

private:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    AssetImporter();
    ~AssetImporter();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Attach(std::shared_ptr<CustomImporter> customImporter);

    void
    Import(_IN_OUT_ Asset *asset,
           _IN_     const std::string& assetFilePath);

private:
    template <typename T>
    void
    ImportDispatch(_IN_OUT_ T                 *asset,
                   _IN_     const std::string& assetFilePath)
    {
        // Find replacement importer.
        auto replacementImporterIter = mCustomImporterReplacementTable.find(int(asset->mAssetType));
        if (replacementImporterIter != mCustomImporterReplacementTable.end())
        {
            for (auto importerIter = replacementImporterIter->second.begin(); importerIter != replacementImporterIter->second.end(); ++importerIter)
            {
                // Load with replacement importer.
                auto replacementSuccess = (*importerIter)->Import(asset, assetFilePath);
                if (replacementSuccess)
                {
                    return;
                }
            }
        }
        else
        {
            // Load with default importer.
            bool defaultSuccess = ImportInternal(asset, assetFilePath);
            if (!defaultSuccess)
            {
                // Find supplement importer.
                auto supplementImporterIter = mCustomImporterSupplementTable.find(int(asset->mAssetType));
                if (supplementImporterIter != mCustomImporterSupplementTable.end())
                {
                    auto supplementSuccess = false;
                    for (auto importerIter = supplementImporterIter->second.begin(); importerIter != supplementImporterIter->second.end(); ++importerIter)
                    {
                        // Load with supplement importer.
                        supplementSuccess = (*importerIter)->Import(asset, assetFilePath);
                        if (supplementSuccess)
                        {
                            return;
                        }
                    }

                    if (!supplementSuccess)
                    {
                        // All load attempts using different importers fail.
                        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(std::string("Encounter unsupported file format: \'" + assetFilePath + "'."));
                    }
                }
            }
        }
    }

    bool
    ImportInternal(Model *model, const std::string& modelFilePath);

private:
    std::unordered_map<int, std::list<std::shared_ptr<CustomImporter>>> mCustomImporterReplacementTable;
    std::unordered_map<int, std::list<std::shared_ptr<CustomImporter>>> mCustomImporterSupplementTable;
};
#pragma warning(default: 4251)

FALCON_ENGINE_API bool
ExtensionSupported(const std::string& filePath, const std::vector<std::string>& fileExtensionSupportedList);

}
