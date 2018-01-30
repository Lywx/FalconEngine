#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineData.h>
namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    // NOTE(Wuxiang): You have to initialize OpenGL context first.
    InitializeWindowPlatform();
    InitializeLoaderPlatform();
}

void
GameEnginePlatform::InitializeContextPlatform()
{
    // NOTE(Wuxiang): GLFW context is initialized with window.
}

void
GameEnginePlatform::InitializeWindowPlatform()
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();
    auto gameEngineData = GameEngineData::GetInstance();

    // Initialize GLFW.
    if (glfwInit())
    {
        GameEngineDebugger::OutputString("GLFW initialization succeeded.\n");
    }
    else
    {
        GameEngineDebugger::OutputString("GLFW initialization failed.\n");
        exit(FALCON_ENGINE_CONTEXT_ERROR);
    }

    // Initialize Context Hints
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
    }

    // Initialize Window Hints
    {
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_VISIBLE, gameEngineSettings->mWindowVisible ? GLFW_TRUE : GLFW_FALSE);
    }

    // Create GLFW context and window.
    auto windowHandle = glfwCreateWindow(gameEngineSettings->mWindowWidth,
                                         gameEngineSettings->mWindowHeight,
                                         gameEngineSettings->mWindowTitle.c_str(),
                                         nullptr, nullptr);

    if (gameEngineSettings->mMouseVisible)
    {
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    if (gameEngineSettings->mMouseLimited)
    {
    }
    else
    {
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Matching GLFW context and window.
    glfwMakeContextCurrent(windowHandle);

    auto window = std::make_shared<GameEngineWindow>(windowHandle);
    window->Initialize();
    gameEngineData->mWindow = window;
}

}

#endif
