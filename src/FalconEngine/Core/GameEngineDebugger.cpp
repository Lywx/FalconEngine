#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Core/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DDebug.h>
#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>
#elif defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLDebug.h>
#endif

namespace FalconEngine
{

std::mutex
GameEngineDebugger::sMutex;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineDebugger::GameEngineDebugger()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineDebugger::Destroy()
{
}

void
GameEngineDebugger::Initialize()
{
#if defined(FALCON_ENGINE_DEBUG_GRAPHICS)
#if defined(FALCON_ENGINE_API_DIRECT3D)
    Direct3DDebugInitialize(GameEnginePlatform::GetInstance()->mData->mDevice);
#elif defined(FALCON_ENGINE_API_OPENGL)
    OpenGLDebugInitialize();
#endif
#endif
}

}
