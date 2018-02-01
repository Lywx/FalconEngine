#include <FalconEngine/Platform/OpenGL/OpenGLGameEnginePlatformData.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformGameEnginePlatformData::PlatformGameEnginePlatformData()
{
}

PlatformGameEnginePlatformData::~PlatformGameEnginePlatformData()
{
}

}

#endif