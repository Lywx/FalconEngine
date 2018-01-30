#include <FalconEngine/Platform/OpenGL/OglRendererData.h>

#include <memory>

#if defined(FALCON_ENGINE_API_OPENGL)
#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Platform/GLFW/GLFWWindowData.h>
#elif defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Platform/Qt/QtWindowData.h>
#endif
namespace FalconEngine
{

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
    mWindowData = std::unique_ptr<PlatformWindowData, PlatformWindowDataDeleter>(
                      new PlatformWindowData(window->mHandle),
                      PlatformWindowDataDeleter());
}

}

#endif