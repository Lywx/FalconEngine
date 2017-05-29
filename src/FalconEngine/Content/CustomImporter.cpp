#include <FalconEngine/Content/CustomImporter.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
CustomImporter::CustomImporter(CustomImporterPolicy assetImportPolicy) :
    mAssetImportPolicy(assetImportPolicy)

{
}

CustomImporter::~CustomImporter()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
CustomImporter::Import(
    _IN_OUT_ Model *                  /* model */,
    _IN_     const std::string&       /* modelFilePath */,
    _IN_     const ModelImportOption& /* modelImportOption */)
{
    return false;
}

}
