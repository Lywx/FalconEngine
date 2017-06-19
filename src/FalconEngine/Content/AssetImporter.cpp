#include <FalconEngine/Content/AssetImporter.h>

#include <FalconEngine/Content/CustomImporter.h>
#include <FalconEngine/Content/ModelImporter.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AssetImporter::AssetImporter()
{
}

AssetImporter::~AssetImporter()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AssetImporter::Attach(std::shared_ptr<CustomImporter> customImporter)
{
    switch (customImporter->mAssetImportPolicy)
    {
    case CustomImporterPolicy::Replacement:
    {
        for (AssetType assetType : customImporter->mAssetTypeList)
        {
            mCustomImporterReplacementTable[int(assetType)].push_back(customImporter);
        }
    }
    break;

    case CustomImporterPolicy::Supplement:
    {
        for (AssetType assetType : customImporter->mAssetTypeList)
        {
            mCustomImporterSupplementTable[int(assetType)].push_back(customImporter);
        }
    }
    break;

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
bool
AssetImporter::ImportInternal(Model *model, const std::string& modelFilePath, const ModelImportOption& modelImportOption)
{
    return ModelImporter::Import(model, modelFilePath, modelImportOption);
}

}
