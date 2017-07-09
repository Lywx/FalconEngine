#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameDebug.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>

namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();
    auto gameEngineData = GameEngineData::GetInstance();

    // Initialize GLFW.
    {
        if (glfwInit())
        {
            GameDebug::OutputString("GLFW initialization succeeded.\n");
        }
        else
        {
            GameDebug::OutputString("GLFW initialization failed.\n");
            glfwTerminate();
        }

        // GLFW Window Hints
        {
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
            glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_VISIBLE, gameEngineSettings->mWindowVisible ? GLFW_TRUE : GLFW_FALSE);
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

        auto window = glfwCreateWindow(gameEngineSettings->mWindowWidth, gameEngineSettings->mWindowHeight, gameEngineSettings->mWindowTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);

        if (gameEngineSettings->mMouseVisible)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }

        if (gameEngineSettings->mMouseLimited)
        {
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        gameEngineData->mWindow = window;
    }

    // Initialize GLEW.
    {
        // NOTE(Wuxiang): Need to initialize glew after window has been created.
        // http://stackoverflow.com/questions/13943825/access-violation-when-using-glew-and-glfw
        if (glewInit() == GLEW_OK)
        {
            GameDebug::OutputString("GLEW initialization succeeded.\n");
        }
        else
        {
            GameDebug::OutputString("GLEW initialization failed.\n");
            glfwTerminate();
        }
    }

}

}
#endif
