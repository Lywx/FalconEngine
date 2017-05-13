#include <FalconEngine/Context/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_PLATFORM_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#endif

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEnginePlatform::GameEnginePlatform()
{
}

GameEnginePlatform::~GameEnginePlatform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEnginePlatform::Initialize(GameEngineData *data, GameEngineSettingsSharedPtr settings)
{
    InitializeExceptPlatform();
    InitializePlatform(data, settings);
}

void
GameEnginePlatform::InitializeExceptPlatform()
{
}

}
