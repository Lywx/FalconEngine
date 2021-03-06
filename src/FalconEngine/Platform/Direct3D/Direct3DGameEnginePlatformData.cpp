#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformGameEnginePlatformData::PlatformGameEnginePlatformData() :
    mFeatureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

PlatformGameEnginePlatformData::~PlatformGameEnginePlatformData()
{
}

}

#endif