#include <FalconEngine/Context/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
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
GameEnginePlatform::Initialize()
{
    InitializeData();
    InitializePlatform();
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEnginePlatform::InitializeData()
{
}

}
