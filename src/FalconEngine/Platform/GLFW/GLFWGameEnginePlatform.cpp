#include <FalconEngine/Core/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Platform/GLFW/GLFWGameEngineWindow.h>
#include <FalconEngine/Platform/GLFW/GLFWLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLGameEnginePlatformData.h>

namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    InitializeDataPlatform();

    // NOTE(Wuxiang): You have to initialize OpenGL context first.
    InitializeWindowPlatform();
    InitializeLoaderPlatform();
}

void
GameEnginePlatform::InitializeDataPlatform()
{
    mData = std::unique_ptr<PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter>(
                new PlatformGameEnginePlatformData(),
                PlatformGameEnginePlatformDataDeleter());
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

    // Initialize GLFW.
    if (glfwInit())
    {
        GameEngineDebugger::OutputString("GLFW initialization succeeded.\n");
    }
    else
    {
        FALCON_ENGINE_THROW_API_EXCEPTION("GLFW initialization failed.\n");
    }

    // Initialize Context Hints
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(FALCON_ENGINE_DEBUG_GRAPHICS)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
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
    // TODO(Wuxiang): A lot of things to do to better the backbuffer format.
    // http://www.glfw.org/docs/latest/window_guide.html
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

    mWindow = std::make_shared<PlatformGameEngineWindow>(windowHandle);
    mWindow->Initialize();
}

}

#endif
