#include <FalconEngine/Input/MouseController.h>

#include <FalconEngine/Context/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_PLATFORM_GLFW)
#include <FalconEngine/Input/Platform/GLFW/GLFWMouseControllerData.h>

namespace FalconEngine
{

void
MouseController::SetPosition(Vector2f position) const
{
    glfwSetCursorPos(mData->mWindow, position.x, position.y);
}

}

#endif
