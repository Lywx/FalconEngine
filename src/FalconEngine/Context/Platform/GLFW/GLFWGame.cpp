#include <FalconEngine/Context/Game.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWInclude.h>

namespace FalconEngine
{

void
Game::UpdateInput()
{
    glfwPollEvents();
}

}

#endif