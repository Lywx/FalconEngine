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
CustomImporter::Import(Model * /* model */, const std::string& /* modelFilePath */)
{
    return false;
}

bool
CustomImporter::Import(Font * /* font */, const std::string& /* fontFilePath */)
{
    return false;
}

}
