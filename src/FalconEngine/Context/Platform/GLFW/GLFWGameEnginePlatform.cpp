#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform(GameEngineData *data, GameEngineSettingsSharedPtr settings)
{
    GLFWwindow *window = nullptr;
    auto settingsGraphics = settings->mGraphics;

    // Initialize GLFW.
    {
        glfwInit();

        // GLFW Window Hints
        {
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
            glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        }

        // OpenGL Context Hints
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
        }

        // OpenGL Framebuffer Hints
        {

        }

        window = glfwCreateWindow(settingsGraphics->mWidth, settingsGraphics->mHeight, settingsGraphics->mTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
    }

    // Initialize GLEW.
    {
        // NOTE(Wuxiang): Need to initialize glew after window has been created.
        // http://stackoverflow.com/questions/13943825/access-violation-when-using-glew-and-glfw
        glewInit();
    }

    data->mWindow = window;
}

}
#endif
