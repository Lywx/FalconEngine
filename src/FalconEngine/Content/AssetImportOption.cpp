#include <FalconEngine/Content/AssetImportOption.h>

namespace FalconEngine
{

const ModelImportOption
AssetImportOption::mModelOption = ModelImportOption(
                                      ModelAccessOption(),
                                      ModelMemoryOption(),
                                      BufferUsage::Static,
                                      IndexType::UnsignedInt);

}
