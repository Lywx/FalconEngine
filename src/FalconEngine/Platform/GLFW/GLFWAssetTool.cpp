#include <FalconEngine/Content/AssetTool.h>

#if defined(FALCON_ENGINE_API_GLAD)
#include <FalconEngine/Platform/GLAD/GLADLib.h>
#endif

#if defined(FALCON_ENGINE_API_GLEW)
#include <FalconEngine/Platform/GLEW/GLEWLib.h>
#endif

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Core/GameEngineDebugger.h>
// NOTE(Wuxiang): Always used GLFW to create OpenGL context.
#include <FalconEngine/Platform/GLFW/GLFWLib.h>

namespace FalconEngine
{
/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AssetTool::OGLInitializeContextPlatform()
{
    glfwInit();

    // GLFW Window Hints
    {
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // NOTE(Wuxiang): Don't show window because this is a console application.
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
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

    auto window = glfwCreateWindow(1, 1, "Compile", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (glewInit() == GLEW_OK)
    {
        GameEngineDebugger::OutputString("GLEW initialization succeeded.\n");
    }
    else
    {
        GameEngineDebugger::OutputString("GLEW initialization failed.\n");
        glfwTerminate();
    }
}

}

#endif