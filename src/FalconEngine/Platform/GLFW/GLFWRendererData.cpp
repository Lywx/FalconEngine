#include <FalconEngine/Platform/GLFW/GLFWRendererData.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <memory>

#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformRendererData, PlatformRendererDataDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformRendererData, PlatformRendererDataDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererData::PlatformRendererData()
{
}

PlatformRendererData::~PlatformRendererData()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformRendererData::Initialize(const std::shared_ptr<GameEngineWindow>& window)
{
    mWindowHandle = window->mHandle;
}

}

#endif