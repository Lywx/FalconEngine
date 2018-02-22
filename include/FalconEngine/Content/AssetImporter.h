#pragma once

#include <FalconEngine/Core/Macro.h>

#include <list>
#include <unordered_map>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Content/CustomImporter.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

namespace FalconEngine
{

class AssetManager;

class CustomImporter;

class Mesh;
class ModelImportOption;

// NEW(Wuxiang): Support multi-threading asset importing.
// @remark Represents a thread-safe asset importer.
FALCON_ENGINE_CLASS_BEGIN AssetImporter final
{
    FALCON_ENGINE_SINGLETON_LEAK_DECLARE(AssetImporter);

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

    template <typename T>
    void
    Import(_IN_OUT_ Asset             * asset,
           _IN_     const std::string & assetFilePath,
           _IN_     const T &           assetImportOption)
    {
        // NEW(Wuxiang): Unified asset importing.
        switch (asset->mAssetType)
        {
        case AssetType::None:
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Asset type is unknown.");
        case AssetType::Audio:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case AssetType::Font:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case AssetType::Shader:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        case AssetType::Model:
            ImportDispatch<Model>(dynamic_cast<Model *>(asset), assetFilePath, assetImportOption);
            break;
        case AssetType::Texture:
            FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        default:
            FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
        }
    }

private:
    template <typename U, typename V>
    void
    ImportDispatch(_IN_OUT_ U                 * asset,
                   _IN_     const std::string & assetFilePath,
                   _IN_     const V &           assetImportOption)
    {
        // Find replacement importer.
        auto replacementImporterIter = mCustomImporterReplacementTable.find(int(asset->mAssetType));
        if (replacementImporterIter != mCustomImporterReplacementTable.end())
        {
            for (auto importerIter = replacementImporterIter->second.begin();
                    importerIter != replacementImporterIter->second.end(); ++importerIter)
            {
                // Load with replacement importer.
                auto replacementSuccess = (*importerIter)->Import(asset, assetFilePath, assetImportOption);
                if (replacementSuccess)
                {
                    return;
                }
            }
        }
        else
        {
            // Load with default importer.
            bool defaultSuccess = ImportInternal(asset, assetFilePath, assetImportOption);
            if (!defaultSuccess)
            {
                // Find supplement importer.
                auto supplementImporterIter = mCustomImporterSupplementTable.find(int(asset->mAssetType));
                if (supplementImporterIter != mCustomImporterSupplementTable.end())
                {
                    auto supplementSuccess = false;
                    for (auto importerIter = supplementImporterIter->second.begin();
                            importerIter != supplementImporterIter->second.end(); ++importerIter)
                    {
                        // Load with supplement importer.
                        supplementSuccess = (*importerIter)->Import(asset, assetFilePath, assetImportOption);
                        if (supplementSuccess)
                        {
                            return;
                        }
                    }

                    if (!supplementSuccess)
                    {
                        // All load attempts using different importers fail.
                        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(
                            std::string("Encounter unsupported file format: \'" + assetFilePath + "'."));
                    }
                }
            }
        }
    }

    bool
    ImportInternal(Model * model, const std::string & modelFilePath, const ModelImportOption & modelImportOption);

private:
    std::unordered_map<int, std::list<std::shared_ptr<CustomImporter>>> mCustomImporterReplacementTable;
    std::unordered_map<int, std::list<std::shared_ptr<CustomImporter>>> mCustomImporterSupplementTable;
};
FALCON_ENGINE_CLASS_END

}
