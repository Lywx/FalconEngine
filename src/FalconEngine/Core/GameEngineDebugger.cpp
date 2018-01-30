#include <FalconEngine/Core/GameEngineDebugger.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OglDebug.h>
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
GameEngineDebugger::Initialize()
{
#if defined(FALCON_ENGINE_API_OPENGL)
    OpenGLDebugInitialize();
#endif
}

}
